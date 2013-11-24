<?php
/**
 * @file
 * drupal_formacion_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function drupal_formacion_rules_default_rules_configuration() {
  $items = array();
  $items['rules_email_content_admin'] = entity_import('rules_config', '{ "rules_email_content_admin" : {
      "LABEL" : "email content admin",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "email" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--rules_exercise" : { "bundle" : "rules_exercise" },
        "node_delete--rules_exercise" : { "bundle" : "rules_exercise" }
      },
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "4" : "4" } },
            "subject" : "[node:type] has been created\\/deleted",
            "message" : "Activity log for site: [site:name] ([site:url]).\\r\\n[node:nid] - [node:titile]\\r\\nCreated: [node:is-new]"
          }
        }
      ]
    }
  }');
  $items['rules_unpublish_rejected_content'] = entity_import('rules_config', '{ "rules_unpublish_rejected_content" : {
      "LABEL" : "unpublish rejected content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "publish" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_update--rules_exercise" : { "bundle" : "rules_exercise" },
        "node_insert--rules_exercise" : { "bundle" : "rules_exercise" }
      },
      "IF" : [
        { "data_is" : { "data" : [ "node:status" ], "value" : "1" } },
        { "data_is" : { "data" : [ "node:field-estado" ], "value" : "2" } }
      ],
      "DO" : [ { "node_unpublish" : { "node" : [ "node" ] } } ]
    }
  }');
  return $items;
}
