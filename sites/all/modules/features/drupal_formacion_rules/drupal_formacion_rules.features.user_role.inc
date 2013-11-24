<?php
/**
 * @file
 * drupal_formacion_rules.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function drupal_formacion_rules_user_default_roles() {
  $roles = array();

  // Exported role: Administrador de contenidos.
  $roles['Administrador de contenidos'] = array(
    'name' => 'Administrador de contenidos',
    'weight' => 3,
  );

  return $roles;
}
