<?php
/**
 * @file
 * Tokens for the training module.
 */

/**
 * Implements hook_token_info().
 */
function training_token_info() {
  $info['types']['task'] = array(
    'name' => t('Tasks'),
    'description' => t('Tokens related to tasks.'),
    'needs-data' => 'task',
  );
  $info['tokens']['task']['id'] = array(
    'name' => t('ID'),
    'description' => t('The unique ID of the tasks.'),
  );
  $info['tokens']['task']['name'] = array(
    'name' => t('Task'),
    'description' => t('Name of the task.'),
  );
  $info['tokens']['task']['uid'] = array(
    'name' => t('User ID'),
    'description' => t('The unique ID of the user.'),
    'type' => 'user',
  );
  $info['types']['current_training'] = array(
    'name' => t('Current training'),
    'description' => t('Tokens related to the current training.'),
  );
  $info['tokens']['current_training']['id'] = array(
    'name' => t('ID'),
    'description' => t('The unique ID of the current training.'),
  );
  $info['types']['num_lottery'] = array(
    'name' => t('Lottery number'),
    'description' => t('Tokens related to the current lottery number.'),
  );
  $info['tokens']['num_lottery']['num'] = array(
    'name' => t('Number'),
    'description' => t('The number of the current lottery.'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function training_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  if ($type == 'task' && !empty($data['task'])) {
    $task = $data['task'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'id':
          $replacements[$original] = $task->id;
          break;
        case 'name':
          $replacements[$original] = $sanitize ? filter_xss($task->name) : $task->name;
          break;
        case 'uid':
          $replacements[$original] = $task->uid;
          break;
      }
    }
    if ($user_tokens = token_find_with_prefix($tokens, 'uid')) {
      module_load_include('tokens', 'user');
      $replacements += token_generate('user', $user_tokens, array('user' => user_load($task->uid)), $options);
    }
  }
  elseif ($type == 'current_training') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'id':
          $replacements[$original] = variable_get('training_current_training', 1);
          break;
      }
    }
  }
  elseif ($type == 'num_lottery') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'num':
          $replacements[$original] = rand(1, 100);
          break;
      }
    }
  }

  return $replacements;
}
