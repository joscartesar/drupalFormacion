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

  // Textarea
  $form['body'] = array(
    '#type' => 'textarea',
    '#default_value' => array_key_exists('body', $data) ? $data['body'] : '',
    '#rows' => 4,
    '#cols' => 3,
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
