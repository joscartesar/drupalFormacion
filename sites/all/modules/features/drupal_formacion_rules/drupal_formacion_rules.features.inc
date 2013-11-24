<?php
/**
 * @file
 * drupal_formacion_rules.features.inc
 */

/**
 * Implements hook_node_info().
 */
function drupal_formacion_rules_node_info() {
  $items = array(
    'rules_exercise' => array(
      'name' => t('Rules exercise'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
