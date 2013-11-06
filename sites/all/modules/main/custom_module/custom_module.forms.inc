<?php

/**
 * Define a custom form
 */
function custom_module_my_custom_form(){
  $form = array();

  //Get the current data stored in DB:
  $data = variable_get('custom_module_my_custom_data', array());

  // Fieldset:
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => 'Mi fieldset',
    '#collapsible' => TRUE,
  );
  // Textfield requiered:
  $form['fieldset']['subject'] = array(
    '#required' => TRUE,
    '#prefix' => '<div class="subject-wrapper">',
    '#type' => 'textfield',
    '#default_value' => array_key_exists('subject', $data) ? $data['subject'] : '',
    '#suffix' => '</div>',
  );

  // Text with machine-name:
  $form['text_source'] = array(
    '#required' => TRUE,
    '#type' => 'textfield',
    '#default_value' => array_key_exists('text_source', $data) ? $data['text_source'] : '',
  );

   // Machine-name input:
  $form['text_source_machine'] = array(
    '#type' => 'machine_name',
    '#default_value' => '',
    '#machine_name' => array(
      'exists' => '_custom_module_text_source_machine_exists', // Check if this value exists
      'source' => array('text_source'), // Input text as source
    ),
  );

  // Textarea
  $form['body'] = array(
    '#type' => 'textarea',
    '#default_value' => array_key_exists('body', $data) ? $data['body'] : '',
    '#rows' => 4,
    '#cols' => 3,
    );

  $form['image_file'] = array(
    '#type' => 'file',
    '#title' => t('Image file'),
    '#description' => t('Allowed extensions: gif png jpg jpeg'),
  );

  // Submit button:
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );

  return $form;
}

/**
 * Implements FORM_ID_validate().
 */
function custom_module_my_custom_form_validate(&$form, &$form_state) {
  if (is_numeric($form_state['values']['subject'])) {
    // Show error :
    form_set_error('subject', t('Enter a string'));
  }
  // Validate and save this file:
  $validators = array(
    'file_validate_extensions' => array('jpeg jpg gif tiff png'),
    'file_validate_size' => array(file_upload_max_size()),
  );
  $dest = 'public://'; // File destine
  if ($file = file_save_upload('image_file', $validators, $dest)) {
    // Save the $file at $form_state
    $form_state['values']['image_file'] = $file;
    // Set as PERMANENT this file:
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
  }
}

/**
 * Implements FORM_ID_submit().
 */
function custom_module_my_custom_form_submit($form, $form_state) {
  // Create data for to be strored in DB with the submitted data.
  $data = array(
    'subject' => check_plain($form_state['values']['subject']), // Santize
    'body' => check_plain($form_state['values']['body']), // Santize
  );
  // Store the submitted data into a Drupal variable:
  // This is saved as new row in varibale table in DB.
  variable_set('custom_module_my_custom_data', $data);

  // Success message:
  drupal_set_message(t('Your form data has been saved correctly'));
}

# # # # # # # # # # # # # #
# # AUXILIARY FUNCTIONS # #
# # # # # # # # # # # # # #

/**
 * Check if text_source_machine_name exists.
 */
function _custom_module_text_source_machine_exists($element, &$form_state) {
  $exists = FALSE;
  if ($element == '1234') {
    $exists = TRUE;
  }
  return $exists;
}
