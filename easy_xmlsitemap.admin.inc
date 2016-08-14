<?php
/**
 * @file
 * Admin forms to manage module
 *
 */

/**
 * 
 * Settings form for module.
 *
 */
function easy_xmlsitemap_settings_form() {
  
  $config      = config('easy_xmlsitemap.settings');
  $last_build_date = $config->get('last_build_date');
  
  $info = $last_build_date != 0 
      ? t('Sitemap file last build time: ') . format_date($last_build_date, 'short') 
      : t('Sitemap file has not built yet.');
  
  $form = array();
  
  $form['build_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sitemap build'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
   );
  
  $form['build_info']['info'] = array(
    '#markup' => '<p>' . $info . '</p>',
  );
  $form['build_info']['actions'] = array('#type' => 'actions');
  $form['build_info']['actions']['build'] = array(
    '#type' => 'submit',
    '#value' => t('Build sitemap now'),
  );
  $form['build_info']['actions']['info'] = array(
    '#markup' => '<div class="description">' . t('This will rebuild XML sitemap.') . '</div>', 
  );
  
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
   );
  
  $form['settings']['base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Default base URL'),
    '#default_value' => $config->get('base_url'),
    '#description' => t('Optional default base URL used for sitemaps and sitemap links, for example: http://example.com, can be left empty.'),
  );
  $form['settings']['rebuild_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Sitemap rebuild frequency'),
    '#options' => array(
      'cron' => t('Any cron run'),
      'daily' => t('Once per day'),
      'manually' => t('Manually only'),
    ),
    '#default_value' => $config->get('rebuild_frequency'),
    '#description' => t('Select time interval for sitemap rebuild.'),
  );
  $form['settings']['excluded_urls'] = array(
    '#type' =>  'textarea',
    '#title' => t('Excluded URLs list (optional)'),
    '#default_value' => $config->get('excluded_urls'),
    '#description' => t('If some URLs should be excluded from sitemap, place these URLs here, one URL per line without domain, for example:') 
    . '<br />403.html'
    . '<br />404.html'
    . '<br />node/123'
    . '<br />some-test-page.html'
  );
  
  $form['settings']['actions'] = array('#type' => 'actions');
  $form['settings']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
  
}

/**
 * Submit actions for form
 * 
 */
function easy_xmlsitemap_settings_form_submit($form, &$form_state) {
  
  global $user;
  $config = config('easy_xmlsitemap.settings');
  
  if ($form_state['clicked_button']['#id'] == 'edit-submit') {

    $config->set('base_url',           trim($form_state['values']['base_url']));
    $config->set('rebuild_frequency',  $form_state['values']['rebuild_frequency']);
    $config->set('excluded_urls',      trim($form_state['values']['excluded_urls']));

    $config->save();
    watchdog('easy_xmlsitemap', t('Settings changed by @user.', array('@user' => $user->name)));
    backdrop_set_message(t('Configuration settings have been saved.'));
  }
  else {
    easy_xmlsitemap_build();
  }
}

