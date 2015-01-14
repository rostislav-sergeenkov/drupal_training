<?php
/**
 * @file
 * Page callbacks for the training module.
 */

/**
 * Renders example form.
 *
 * @param array $arg
 *  Id of example form.
 *
 * @return array|mixed
 *   The form array.
 */
function training_example_form_callback($arg) {
  return drupal_get_form($arg, array());
}

/**
 * Creates example form.
 *
 * @param array $form
 *   Array of form elements.
 * @param array $form_state
 *   Array of form parameters.
 *
 * @return array
 *   Array of form elements.
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
