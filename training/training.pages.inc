<?php
/**
 * @file
 * Page callbacks for the training module.
 */

/**
 * Builds form that demonstrates example security in Drupal.
 */
function training_security_form($form, &$form_state) {
  $form['markup_security'] = array(
    '#prefix' => '<div id = "training-security-text">',
    '#suffix' => '</div>',
    '#markup' => '',
    '#tree' => TRUE,
  );
  $form['markup_security']['text_security'] = array(
      '#type' => 'textarea',
      '#title' => t('Secure text'),
  );
  $form['markup_security']['submit_security'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#ajax' => array(
      'callback' => 'training_security_display_text',
      'wrapper' => 'training-security-text',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Displays text after ajax submit for training_security_form.
 */
function training_security_display_text($form, &$form_state) {
  $output = check_plain($form_state['values']['markup_security']['text_security']);
  $form['markup_security']['#markup'] = $output;

  return $form['markup_security'];
}

/**
 * Renders page callback for training/dates.
 *
 * @return array
 */
function training_dates_callback() {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  $output = ctools_modal_text_button('Click me to show date', 'training/dates/nojs/form', 'Click', 'ctools-modal-date-class');
  $settings = array(
    'date-class' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 300,
        'height' => 300,
      ),
      'animation' => 'fadeIn',
    ),
  );

  return array(
    array(
      '#type' => 'markup',
      '#markup' => $output,
    ),
    array(
      '#attached' => array(
        'js' => array(
          array(
            'data' => $settings,
            'type' => 'setting',
          ),
        ),
      ),
    ),
  );
}

/**
 * Renders page callback for training/dates/%ctools_js/form.
 *
 * @param $js
 *   Determines the availability java script.
 *
 * @return array
 *   Returns renderable array if parameter does not exist.
 */
function training_dates_form_callback($js) {
  global $user;
  $date = new DateObject($user->created);
  $date_now = date_now($user->timezone);
  $end_date = new DateObject('31 Dec 2015');
  $duration = $date_now->difference($end_date, 'days');
  $output = array(
    t('Date of registration !name:', array('!name' => $user->name)),
    date_format_date($date, 'custom', 'd F Y'),
    t('Left until the new year'),
    format_plural($duration, '1 day', '@count days'),
  );
  if (!$js) {
    return array(
      array(
        '#type' => 'markup',
        '#markup' => implode('<br />', $output),
      ),
    );
  }
  ctools_include('modal');
  ctools_include('ajax');
  $commands[] = ctools_modal_command_display(t('Date'), implode('<br />', $output));
  print ajax_render($commands);
  exit;
}

/**
 * Renders page callback for training/i18n.
 *
 * @return array
 */
function training_i18n_callback() {
  $output = array(
    t('Some text.'),
    t('Some text with !token.', array('!token' => 5)),
    l(t('Home'), t('<front>')),
    format_plural(rand(1,100), '1 task', '@count tasks'),
  );

  return array(
    array(
      '#type' => 'markup',
      '#markup' => implode('<br />', $output),
    ),
    array(
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'training') . '/js/training_i18n.js',
        ),
      ),
    ),
  );
}

/**
 * Renders a page Example CTools Javascript.
 *
 * @return array
 */
function training_js_callback() {
  global $user;
  $settings = array(
    'user_id' => $user->uid,
    'random_num' => rand(),
  );
  $output = t('User ID = %uid', array(
    '%uid' => $user->uid,
  ));

  return array(
    array(
      '#type' => 'markup',
      '#markup' => $output,
    ),
    array(
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'training') . '/js/training.js',
          array(
            'data' => $settings,
            'type' => 'setting',
          ),
        ),
      ),
    ),
  );
}

/**
 * Renders a page Example CTools Ajax.
 *
 * @return string
 */
function training_ajax_callback() {
  ctools_include('ajax');
  $output = ctools_ajax_text_button('Click me!', 'training/ctools/ajax/callback-text', 'Click');

  return $output;
}

/**
 * Renders page callback for training/ctools/ajax/callback-text.
 */
function training_ajax_callback_text() {
  drupal_add_js(drupal_get_path('module', 'training') . '/js/training.js');
  $commands = array();
  $commands[] = array(
    'command' => 'reload',
    'some_param' => rand(2, 4),
  );
  print ajax_render($commands);
  exit;
}

/**
 * Renders page callback for training/ctools/cleanstring.
 *
 * @return string
 */
function training_cleanstring_callback() {
  ctools_include('cleanstring');
  $output = array();
  $output[] = ctools_cleanstring('some text /ё @12-5 [test]');
  $output[] = ctools_cleanstring('some text', array(
    'separator' => ' ',
  ));
  $output[] = ctools_cleanstring('some text', array(
    'ignore words' => 'text',
    'replacements' => array(
      'some' => 'Some',
    ),
  ));
  $output[] = ctools_cleanstring('некоторый текст', array(
    'transliterate' => TRUE,
    'max length' => 15,
  ));

  return implode('<br />', $output);
}

/**
 * Builds dynamic form.
 */
function training_dependent_form($form, &$form_state) {
  ctools_include('dependent');
  $form['radios_buttons'] = array(
    '#type' => 'radios',
    '#options' => array(
      'one' => 'I',
      'two' => 'II',
      'three' => 'III',
    ),
    '#default_value' => 'two',
  );
  $form['dependent_on_radios_buttons'] = array(
    '#type' => 'fieldset',
    '#dependency' => array(
      'radio:radios_buttons' => array(
        'one',
      ),
    ),
    '#tree' => TRUE,
    'text' => array(
      '#type' => 'textfield',
      '#title' => t('Enter some text'),
    ),
    'another_text' => array(
      '#type' => 'textfield',
      '#title' => t('Enter another text'),
    ),
    'dependent_on_text' => array(
      '#type' => 'fieldset',
      '#title' => 'I depend on text',
      '#dependency' => array(
        'edit-dependent-on-radios-buttons-text' => array(
          'Show me please',
        ),
      ),
      'button' => array(
        '#type' => 'button',
        '#value' => t('Some button'),
      ),
    ),
  );
  $form['submit_dependent'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#submit'][] = 'training_dependent_submit';

  return $form;
}

/**
 * Submits form training_dependent_form.
 */
function training_dependent_submit($form, &$form_state) {
  drupal_set_message(t('Here'));
}

/**
 * Renders page callback for training/ctools/math.
 *
 * @return string
 */
function training_math_callback() {
  ctools_include('math-expr');
  $expr = new ctools_math_expr();
  $expr->evaluate('f(x, y)=x+y');
  $result = $expr->evaluate('f(10, 20)');

  return t('Result is !result', array(
    '!result' => $result,
  ));
}

/**
 * Renders page callback for training/ctools/modal.
 *
 * @return string
 */
function training_modal_callback() {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  $output = ctools_modal_text_button('Click me to show modal', 'training/ctools/modal/nojs/form', 'Click', 'ctools-modal-some-class');
  $settings = array(
    'some-class' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 500,
        'height' => 300,
      ),
      'animation' => 'fadeIn',
    ),
  );

  return array(
    array(
      '#type' => 'markup',
      '#markup' => $output,
    ),
    array(
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'training') . '/js/training.js',
          array(
            'data' => $settings,
            'type' => 'setting',
          ),
        ),
      ),
    ),
  );
}

/**
 * Renders page callback for training/ctools/modal/%ctools_js/form.
 *
 * @param $js
 *   Determines the availability java script.
 *
 * @return string
 */
function training_modal_form_callback($js) {
  if (!$js) {
    return drupal_get_form('training_modal_form');
  }
  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Demo AJAX form'),
  );
  $commands = ctools_modal_form_wrapper('training_modal_form', $form_state);
  if (!empty($form_state['executed'])) {
    $commands = array();
    $commands[] = ctools_modal_command_display(t('Some title'), '<strong>Hey</strong>, we are here');
    //$commands[] = ctools_modal_command_dismiss(); //hides modal
  }
  print ajax_render($commands);
  exit;
}

/**
 * Builds example modal form.
 */
function training_modal_form($form, &$form_state) {
  $form = array(
    'submit_modal' => array(
      '#type' => 'submit',
      '#value' => t('Sample button'),
    ),
  );

  return $form;
}

/**
 * Submits form training_modal_form.
 */
function training_modal_form_submit($form, &$form_state) {
  drupal_set_message(t('Here'));
}

/**
 * Renders page callback for training/ctools/tabs.
 *
 * @return string
 */
function training_tabs_callback() {
  ctools_include('menu');
  $tab_1 = array(
    'title' => 'First tab',
    'href' => 'training/ctools/tabs/tab1',
  );
  $tab_2 = array(
    'title' => 'Second tab',
    'href' => 'training/ctools/tabs/tab2',
  );
  ctools_menu_add_tab($tab_1);
  ctools_menu_add_tab($tab_2);
  if (arg(3) == 'tab2') {
    return t('Tab 2 content');
  }

  return t('Tab 1 content');
}

/**
 * Renders page callback for training/ctools/object-cache.
 *
 * @return string
 */
function training_object_cache_callback() {
  ctools_include('object-cache');
  $obj = new stdClass();
  $obj->title = 'my-item';
  $obj->data = training_menu();
  ctools_object_cache_set('training_object', $obj->title, $obj);
  //$obj = ctools_object_cache_get('training_object', 'my-item', TRUE);

  return t('Lorem ipsum');
}

/**
 * Renders page callback for training/files.
 *
 * Selects rows from table 'file_managed'. Renders tables with pager and sorting.
 * Builds AJAX text button.
 *
 * @return array
 *   Renderable array.
 */
function training_files_callback() {
  global $user;
  $array_id = array();
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  $output = ctools_modal_text_button('Click me to upload file', 'training/files/nojs/load_form', 'Click', 'ctools-modal-file-load-form-class');
  $header = array(
    array('data' => t('UID'), 'id' => 'header-uid'),
    array('data' => t('FID'), 'field' => 'fid'),
    array('data' => t('Filename'), 'field' => 'filename'),
    array('data' => t('URI'), 'field' => 'uri'),
    array('data' => t('Status'), 'field' => 'status'),
    array('data' => t('Download')),
  );
  $rows = array();
  $query = db_select('file_managed', 'fm');
  $query
    ->fields('fm', array('fid','uid', 'filename', 'uri', 'status'));
  $result = $query
    ->extend('PagerDefault')
    ->limit(10)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->execute()->fetchAll();
  if (!empty($query)) {
    foreach ($result as $value) {
      $array_id[$value->fid] = $value->uid;
      $file = file_load($value->fid);
      $url = file_create_url($file->uri);
      $rows[] = array(
        'data' => array(
          array('data' => $value->uid, 'class' => 'uid-cell'),
          $value->fid,
          check_plain($value->filename),
          $value->uri,
          $value->status,
          l(t('Download'), $url),
          ),
        'id' => 'fid-cell-' . $value->fid,
      );
    }
  }
  $settings = array(
    'user_id' => $user->uid,
    'array_id' => $array_id,
    'file-load-form-class' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 500,
        'height' => 300,
      ),
      'animation' => 'fadeIn',
    ),
  );

  return array(
    array(
      '#type' => 'markup',
      '#markup' => $output,
    ),
    array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
    array(
      '#theme' => 'pager',
      '#tags' => array('<<', '<', '', '>', '>>'),
    ),
    array(
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'training') . '/js/training_files.js',
          array(
            'data' => $settings,
            'type' => 'setting',
          ),
        ),
        'css' => array(
          drupal_get_path('module', 'training') . '/css/training.css',
        ),
      ),
    ),
  );
}

/**
 * Renders page callback for training/files/%ctools_js/load_form.
 *
 * @param $js
 *   Determines the availability java script.
 *
 * @return string
 */
function training_load_form_callback($js) {
  if (!$js) {
    return drupal_get_form('training_modal_load_files_form');
  }
  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Upload files form'),
  );
  $commands = ctools_modal_form_wrapper('training_modal_load_files_form', $form_state);
  if (!empty($form_state['executed'])) {
    $commands = array();
    $commands[] = ctools_ajax_command_reload();
    $commands[] = ctools_modal_command_dismiss();
  }
  print ajax_render($commands);
  exit;
}

/**
 * Builds modal form to upload files.
 */
function training_modal_load_files_form($form, &$form_state) {
  $form = array(
    'file_upload' => array(
      '#type' => 'managed_file',
      '#title' => 'Upload file',
      '#upload_location' => 'private://upload',
      '#upload_validators' => array(
        'file_validate_extensions' => array(),
      ),
    ),
    'submit_upload' => array(
      '#type' => 'submit',
      '#value' => 'Submit',
    ),
  );

  return $form;
}

/**
 * Submits form training_modal_load_files_form.
 */
function training_modal_load_files_form_submit($form, &$form_state) {
  $file = file_load($form_state['values']['file_upload']);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
}

/**
 * Renders a page with listing of text message.
 *
 * Selects rows from table 'text_message'. Renders tables with pager and sorting.
 *
 * @return array
 *   Renderable array.
 */
function training_text_message_callback() {
  $header = array(
    array('data' => t('Num'), 'field' => 'id'),
    array('data' => t('Author'), 'field' => 'name'),
    array('data' => t('Title'), 'field' => 'title'),
    array('data' => t('Text'), 'field' => 'body'),
    array('data' => t('Edit')),
  );
  $rows = array();
  $query = db_select('text_message', 'tm');
  $query->innerJoin('users', 'u', 'tm.uid = u.uid');
  $query
    ->fields('tm', array('id', 'title', 'body'))
    ->fields('u', array('name'));
  $result = $query
    ->extend('PagerDefault')
    ->limit(5)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->execute()->fetchAll();
  if (!empty($query)) {
    foreach ($result as $value) {
      $rows[] = array(
        $value->id,
        $value->name,
        check_plain($value->title),
        check_plain($value->body),
        l(t('Edit'), 'training/message/edit/' . $value->id),
      );
    }
  }

  return array(
    array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
    array(
      '#theme' => 'pager',
      '#quantity' => 5,
      '#tags' => array('<<', '<', '', '>', '>>'),
    ),
  );
}

/**
 * Builds form to add text message.
 */
function text_message_form($form, &$form_state, $arg = NULL) {
  $form = array();
  $form['title_msg'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
    '#required' => TRUE,
  );
  $form['body_msg'] = array(
    '#type' => 'textarea',
    '#title' => 'Text',
    '#required' => TRUE,
  );
  $form['id_msg'] = array(
    '#type' => 'hidden',
    '#value' => NULL,
  );
  $form['submit_msg'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );
  $form['#submit'][] = 'text_message_submit';

  if (isset($arg)) {
    $query = db_select('text_message', 'tm');
    $query
      ->fields('tm', array('title', 'body'))
      ->condition('tm.id', $arg);
    $result = $query->execute()->fetchAssoc();
    $form['title_msg']['#default_value'] = $result['title'];
    $form['body_msg']['#default_value'] = $result['body'];
    $form['id_msg']['#value'] = $arg;
  }

  return $form;
}

/**
 * Submits form text_message_form.
 *
 * Adds or updates text message.
 */
function text_message_submit($form, &$form_state) {
  global $user;
  if (isset($form_state['values']['id_msg'])) {
    $entity = entity_load('text_msg', array($form_state['values']['id_msg']));
    $wrapper = entity_metadata_wrapper('text_msg', $entity[$form_state['values']['id_msg']]);
    $wrapper->title = check_plain($form_state['values']['title_msg']);
    $wrapper->body = check_plain($form_state['values']['body_msg']);
    $wrapper->save();
  }
  else {
    $entity = entity_create('text_msg', array(
      'uid' => $user->uid,
      'type' => rand(),
      'title' => check_plain($form_state['values']['title_msg']),
      'body' => check_plain($form_state['values']['body_msg']),
    ));
    entity_save('text_msg', $entity);
  }
  drupal_goto('training/message');
}

/**
 * Renders Entity Example page.
 *
 * @return string
 */
function training_example_entity_callback() {
  global $user;
  $entity = entity_create('training_item', array(
    'uid' => $user->uid,
    'short_description' => rand(),
  ));
  entity_save('training_item', $entity);

  return t('lorem ipsum');
}

/**
 * Creates example form.
 */
function training_google_form($form, &$form_state) {
  $form = array();
  $form['group'] = array(
    '#type' => 'fieldset',
    '#title' => 'group',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['group']['text'] = array(
    '#type' => 'textfield',
    '#title' => 'title',
  );
  $form['group']['text2'] = array(
    '#type' => 'textfield',
    '#title' => 'title2',
    '#required' => TRUE,
  );
  $form['#attached']['css'] = array(
    //Path to the css file
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('ok'),
  );

  return $form;
}

/**
 * Renders list of links on other theme pages.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_theme_html() {
  $array_items = array(
    l(t('List'), 'training/theme/list'),
    l(t('Table'), 'training/theme/table'),
    l(t('Image'), 'training/theme/image'),
    l(t('Access'), 'training/theme/access'),
  );

  return theme('item_list', array(
    'items' => $array_items,
    'type' => 'ol',
    'title' => t('Links to themes'),
  ));
}

/**
 * Renders sample table at Table theme page.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_theme_table() {
  $my_header = array(
    t('header 1'),
    t('header 2'),
    t('header 3'),
  );
  $rows = array(
    array(
      'data' => array('1', array('data' => t('Oleg'), 'colspan' => 2)),
      'class' => array('rowClass'),
    ),
    array(
      'data' => array('2', array('data' => t('Oleg'), 'colspan' => 2)),
      'class' => array('rowClass'),
    ),
  );
  $caption = t('Theme table sample');
  $attributes = array(
    'id' => 'table-test',
  );

  return theme('table', array(
    'header' => $my_header,
    'rows' => $rows,
    'attributes' => $attributes,
    'caption' => $caption,
  ));
}

/**
 * Renders list of images with default styles.
 *
 * Moves the image to the selected address. Applies default styles to image.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_image_callback() {
  $output = array();
  $file_path = drupal_realpath('modules/image/sample.png');
  $source = (object) array(
    'uid' => 1,
    'uri' => $file_path,
    'filename' => basename($file_path),
    'filemime' => file_get_mimetype($file_path),
  );
  $directory = 'public://';
  file_copy($source, $directory, $replace = FILE_EXISTS_REPLACE);
  $array_style = image_styles();
  foreach ($array_style as $val) {
    $style_name = $val['name'];
    $path = 'public://sample.png';
    $attributes = array(
      'class' => 'simple-image',
    );
    $output[] = theme('image_style', array(
     'style_name' => $style_name,
     'path' => $path,
     'attributes' => $attributes,
    ));
  }

  return theme('item_list', array(
    'items' => $output,
    'type' => 'ol',
    'title' => t('Default image styles'),
  ));
}

/**
 * Renders different content for users with Access protected content permission.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_access_callback() {
  if (user_access('train_theme')) {
    return t('Custom access for rendered content');
  }
  else {
   return t('Custom access inversed for rendered content');
  }
}

/**
 * Renders page for menu item Training Landing Page.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_page_html() {
  return t('This is the landing page of the Training module');
}

/**
 * Renders page for menu item Callback Menu Item.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_menu_callback() {
  return t('The menu entry for this page is of type MENU_CALLBACK');
}

/**
 * Renders page for menu item Tabs Pages.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_menu_tabs_default() {
  return t('This is the "tabs" menu entry');
}

/**
 * Renders page with tabs and dynamic content.
 *
 * @param array $arg
 *   Argument in URL /$arg.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_menu_tabs($arg) {
  return t('This is the tab "%arg" in the "basic tabs" example', array('%arg' => $arg));
}

/**
 * Renders page for menu item Menu arguments.
 *
 * @param array $arg1
 *   First argument in training/menu/arguments/$arg1/$arg2.
 * @param array $arg2
 *   Second argument in training/menu/arguments/$arg1/$arg2.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_menu_arguments($arg1 = NULL, $arg2 = NULL) {
  $output = '';
  if (!empty($arg1)) {
    $output .=  t('Argument 1=%arg', array('%arg' => $arg1)) . '</br>';
  }
  if (!empty($arg2)) {
    $output .=  t('Argument 2=%arg', array('%arg' => $arg2));
  }

  return $output;
}

/**
 * Renders page for menu item Menu argument before display.
 *
 * @param array $arg
 *   Argument in training/menu/placeholder/$arg/display.
 *
 * @return string
 *   String contents HTML tags for custom layout.
 */
function training_menu_arguments_display($arg) {
  return '<div>' . $arg . '</div>';
}

/**
 * Renders page for menu item Menu preprocessing argument.
 *
 * @param array $arg
 *   Argument that returns by function  digit_load($arg).
 *
 * @see digit_load()
 *
 * @return string
 *   String contents HTML tags for custom layout or error 403 if argument is empty.
 */
function training_menu_arguments_preprocessing($arg) {
  if (!empty($arg)) {
    return '<div>' . $arg . '</div>';
  }
  else{
    return MENU_NOT_FOUND;
  }
}
