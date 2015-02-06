<?php
/**
 * @file
 * Rules for the training module.
 */

/**
 * Implements hook_rules_event_info().
 */
function training_rules_event_info() {
  $items = array(
    'training_event' => array(
      'label' => t('Training event'),
      'group' => t('Training'),
    ),
    'lottery' => array(
      'label' => t('Lottery event'),
      'group' => t('Lottery'),
    ),
  );

  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function training_rules_condition_info() {
  return array(
    'training_rules_condition' => array(
      'label' => t('Training condition'),
      'parameter' => array(
        'text1' => array('label' => t('Text 1'), 'type' => 'text'),
        'text2' => array('label' => t('Text 2'), 'type' => 'text'),
      ),
      'base' => 'training_rules_condition',
      'group' => t('Training'),
    ),
    'lottery_condition' => array(
      'label' => t('Lottery condition'),
      'base' => 'training_lottery_rules_condition',
      'group' => t('Lottery'),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function training_rules_action_info() {
  return array(
    'training_action' => array(
      'label' => t('Some sample action'),
      'parameter' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'group' => t('Training'),
      'base' => 'training_rules_action',
    ),
    'lottery_action' => array(
      'label' => t('Lottery action'),
      'parameter' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Lottery message'),
          'sanitize' => TRUE,
          'translatable' => TRUE,
        ),
        'num_lottery' => array(
          'type' => 'text',
          'label' => t('Lottery number'),
          'sanitize' => TRUE,
          'translatable' => TRUE,
        ),
      ),
      'group' => t('Lottery'),
      'base' => 'training_lottery_rules_action',
    ),
  );
}

/**
 * Acts some custom action for training needs.
 */
function training_rules_action($user) {
  dpm($user);
  dpm(t('In action'));
}

/**
 * Acts custom action for lottery event.
 */
function training_lottery_rules_action($user, $message, $num_lottery) {
  drupal_set_message(filter_xss_admin($message));
  $obj = new stdClass();
  $cid = 'cache_for_message_' . $user->uid;
  $cache_obj = cache_get('cache_for_message_' . $user->uid, 'cache_training_lottery');
  if (!$cache_obj) {
    $array_data[] = $num_lottery;
    $obj->lottery_num = $array_data;
    cache_set($cid, $obj, 'cache_training_lottery', CACHE_PERMANENT);
  }
  else {
    $array_data = $cache_obj->data->lottery_num;
    $array_data[] = $num_lottery;
    $obj->lottery_num = $array_data;
    cache_set($cid, $obj, 'cache_training_lottery', CACHE_PERMANENT);
  }
}

/**
 * Checks custom condition for training needs.
 */
function training_rules_condition($text1, $text2) {
  dpm($text1);
  dpm($text2);

  return TRUE;
}

/**
 * Checks custom condition for lottery events.
 *
 * @return bool
 *   Returns true if lottery code is 'success'.
 */
function training_lottery_rules_condition() {
  $success = _training_lottery_generator_success();
  if ($success == 'success') {
    return TRUE;
  }

  return FALSE;
}
