<?php
/**
 * Page callback function
 * Rendering page for form example
 * @param $arg
 * @return array|mixed
 */
function training_example_form_callback($arg){
  return drupal_get_form($arg);
}

/**
 * Page callback function
 * Rendering Item List that items are links on other theme pages
 * @return string
 * @throws \Exception
 */
function training_theme_html(){
  $array = array(
    '<a href="theme/list">List</a>',
    '<a href="theme/table">Table</a>',
    '<a href="theme/image">Image</a>',
    '<a href="theme/access">Access</a>',
  );

return theme('item_list', array(
  'items' => $array,
  'type' => 'ol',
  'title' => 'Links to themes',
));
}

/**
 * Page callback function
 * Rendering Table Table theme page
 * @return string
 * @throws \Exception
 */

function training_theme_table(){
  $my_header = array(
    'header 1',
    'header 2',
    'header 3',
  );
  $rows = array(
    array(
      'data' => array('1',array('data' => 'Oleg', 'colspan' => 2), ),
      'class' => array('rowClass'),
      ),
      array(
        'data' => array('2',array('data' => 'Oleg', 'colspan' => 2), ),
        'class' => array('rowClass'),
      ),
  );
  $caption = 'Theme table sample';
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
 * Page callback function
 * Rendering list of images with default styles
 * @return string
 * @throws \Exception
 */
function training_image_callback(){
  $file_path = drupal_realpath('modules/image/sample.png');
  $source = (object)array(
    'uid' => 1,
    'uri' => $file_path,
    'filename' => basename($file_path),
    'filemime' => file_get_mimetype($file_path),
  );
  $directory = 'public://';
  file_copy($source, $directory, $replace = FILE_EXISTS_REPLACE);
  $output = '';
  $array_style=image_styles();
  foreach ($array_style as $val){
    $style_name = $val['name'];
    $path = 'public://sample.png';
    $attributes = array(
    'class' => 'simple-image',
    );
    $output .= '<li>' . theme('image_style', array(
   'style_name' => $style_name,
   'path' => $path,
   'attributes' => $attributes,
    )) . '</li>';
  }
  return '<ul>' . $output . '</ul>';
}

/**
 * Page callback function
 * Rendering different content for users with Access protected content permission
 * @return string
 * @throws \Exception
 */
function training_access_callback(){
  if (user_access('train_theme')){
    return 'Custom access for rendered content';
  }
  else {
   return  'Custom access inversed for rendered content';
  }
}

/**
 * Page callback function
 * @return string
 */
function training_page_html(){
  return 'This is the landing page of the Training module';
}

/**
 * Page callback function
 * @return string
 */
function training_menu_callback(){
  return 'The menu entry for this page is of type MENU_CALLBACK';
}

/**
 * Page callback function
 * @return string
 */
function training_menu_tabs_default(){
  return 'This is the "tabs" menu entry';
}

/**
 * Page callback function
 * @param $arg - argument in training/menu/tabs/$arg
 * @return string
 */
function training_menu_tabs($arg){
  return 'This is the tab "'.$arg.'" in the "basic tabs" example';
}

/**
 * Page callback function
 * @param $arg1 - first argument in training/menu/arguments/$arg1/$arg2
 * @param $arg2 - second argument in training/menu/arguments/$arg1/$arg2
 * @return string
 */
function training_menu_arguments($arg1=NULL,$arg2=NULL){
  $output = '';
  if (!empty($arg1)) {
    $output .=  'Argument 1 =' .  $arg1 . '</br>';
  }
  if (!empty($arg2)) {
    $output .=  'Argument 2 =' .  $arg2;
  }
  return $output;
}

/**
 * Page callback function
 * @param $arg - argument in training/menu/placeholder/$arg/display
 * @return string
 */
function training_menu_arguments_display($arg){
  return '<div>' . $arg . '</div>';
}

/**
 * Page callback function
 * @param $arg - returns by function  digit_load($arg)
 * @return string
 */
function training_menu_arguments_preprocessing($arg){
  if(!empty($arg)){
    return '<div>' . $arg . '</div>';
  }
  else{
    return MENU_NOT_FOUND;
  }
}