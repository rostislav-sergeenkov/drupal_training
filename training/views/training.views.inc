<?php
/**
 * @file
 * Provide views data for modules training.
 */

/**
 * Implements hook_views_data.
 */
function training_views_data() {
  $data['training_exchange']['table']['group'] = t('Exchange');
  $data['training_exchange']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Exchange'),
    'help' => t('Exchange table contains rate info'),
  );
  $data['training_exchange']['id'] = array(
    'title' => t('Exchange ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['training_exchange']['char_code'] = array(
    'title' => t('Char code'),
    'help' => t('Char code of currency'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['training_exchange']['name'] = array(
    'title' => t('Name currency'),
    'help' => t('Name of currency'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['training_exchange']['rate'] = array(
    'title' => t('Rate currency'),
    'help' => t('Rate of currency'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
