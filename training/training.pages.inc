<?php

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