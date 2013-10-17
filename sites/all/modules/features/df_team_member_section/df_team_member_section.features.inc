<?php
/**
 * @file
 * df_team_member_section.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function df_team_member_section_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function df_team_member_section_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function df_team_member_section_image_default_styles() {
  $styles = array();

  // Exported image style: 100_100px.
  $styles['100_100px'] = array(
    'name' => '100_100px',
    'effects' => array(
      1 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => 100,
          'height' => 100,
          'anchor' => 'center-center',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function df_team_member_section_node_info() {
  $items = array(
    'tb_team_member' => array(
      'name' => t('tb team member'),
      'base' => 'node_content',
      'description' => t('cada uno de los integrantes del equipo de think big'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
