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
  $config = config('easy_xmlsitemap.settings');
  $last_build_date = state_get('easy_xmlsitemap_last_build_date', 0);
  
  $info = $last_build_date != 0 
      ? t('Sitemap last build time: ') . format_date($last_build_date, 'short') 
      : t('Sitemap has not built yet.');
  
  $site_langs = language_list(TRUE, TRUE);

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
  $form['build_info']['build'] = array(
    '#type' => 'submit',
    '#value' => t('Build sitemap now'),
    '#attributes' => array(
      'class' => array('button-primary'),
    ),
  );
  $form['build_info']['actions']['info'] = array(
    '#markup' => '<div class="description">' . t('This will rebuild sitemap immediately.') . '</div>', 
  );
  
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['settings']['force_https'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force "https" protocol for URLs in sitemap.'),
    '#default_value' => $config->get('force_https'),
    '#description' => t('Can be used for sites behind SSL-proxy like Cloudflare.'),
  );
  
  $form['settings']['base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Default base URL (optional)'),
    '#default_value' => $config->get('base_url'),
    '#description' => t('Optional replacement for base URL, should be used instead of actual domain for sitemap links, for example: http://example.com. In most cases can be left empty.'),
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
    '#title' => t('Excluded URLs list:'),
    '#default_value' => $config->get('excluded_urls'),
    '#description' => t('If URL should be excluded from sitemap, place one URL per line without domain part, see an example below:') 
    . '<br />403.html'
    . '<br />404.html'
    . '<br />node/123'
    . '<br />' . t('Multiple similar URLs can be selected by using asterisk wildcard (*), for example:')
    . '<br /><em>post-*</em>,'
    . '<br />' . t('so all URLs starting with post- (such as post-123 or post-about-cat.html) will be excluded from sitemap.'),
    '#prefix' => '<b>' . t('Exclusions:') . '</b>'
    
  );
  if (count($site_langs) > 1) {
    $form['settings']['excluded_langs'] = array(
      '#type' =>  'checkboxes',
      '#title' => t('Exclude from sitemap all pages for selected language:'),
      '#options' => $site_langs,
      '#default_value' => $config->get('excluded_langs'),
      '#description' => t('You might want do not include to sitemap links to pages for specific language.'), 
    );
  }
  if (module_exists('seo_meta')) {
    $form['settings']['seo_meta_integration'] = array(
      '#type' => 'checkbox',
      '#title' => t('Exclude also pages with "noindex" value of meta tag "robots".'),
      '#default_value' => $config->get('seo_meta_integration'),
      '#description' => t('Your site have module "SEO Meta Tags" enabled, so "noindex" in "robots" can be used for excluding pages from sitemap.'),
      '#prefix' => '<b>' . t('"SEO Meta Tags" module integration:') . '</b>',
    );
  }
  
  $form['settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
    '#attributes' => array(
      'class' => array('button-primary'),
    ),
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
    $config->set('force_https',        $form_state['values']['force_https']);
    $config->set('base_url',           trim($form_state['values']['base_url']));
    $config->set('rebuild_frequency',  $form_state['values']['rebuild_frequency']);
    $config->set('excluded_urls',      trim($form_state['values']['excluded_urls']));
    if (isset($form_state['values']['excluded_langs'])) {  
      $config->set('excluded_langs',   $form_state['values']['excluded_langs']);
    }
    if (isset($form_state['values']['seo_meta_integration'])) {  
      $config->set('seo_meta_integration',   $form_state['values']['seo_meta_integration']);
    }
    $config->save();
    watchdog('easy_xmlsitemap', t('Settings changed by @user.', array('@user' => $user->name)));
    backdrop_set_message(t('Configuration settings have been saved.'));
  }
  else {
    easy_xmlsitemap_build();
  }
}
