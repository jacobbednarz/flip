<?php

/**
 * @file
 * Administration file for Flip.
 */

function flip_configure_settings() {
  $form = array();
  $flips = flip_get_all();

  // Loop over every registered feature toggle and build a checkbox item to
  // allow it to be enabled.
  foreach ($flips as $name => $feature_data) {
    $data = unserialize($feature_data->data);

    // Ensure we are only dealing with correct data structures.
    if (!is_array($data)) {
      continue;
    }

    $form['available_feature_toggles']["flip_{$name}_enabled"] = array(
      '#type' => 'checkbox',
      '#title' => (!empty($data['name'])) ? $data['name'] : '',
      '#description' => (!empty($data['description'])) ? $data['description'] : '',
      '#default_value' => variable_get("flip_{$name}_enabled", 0),
    );
  }

  return system_settings_form($form);
}
