<?php


/**
 * Implementation of hook_drush_command().
 */
function randlog_drush_command() {
  $items['randlog'] = array(
    'description' => 'Login to a random user\'s account.',
    'options' => array(
      'roles' => 'A list of roles to limit the the list from which the random user is chosen.  The Authenticated User is automatic and does not need to be specified.',
      'not-roles' => 'A list of roles to exclude from the the list from which the random user is chosen.',
      'path' => 'Optional path to redirect to after logging in.',
      'browser' => 'Optional value denotes which browser to use (defaults to operating system default). Set to 0 to suppress opening a browser.',
    ),
    'aliases' => array('rl'),
  );
  return $items;
}


/**
 * Pick a user at random and return a login link
 *
 * @return
 *   Login URL, launched in a browser by default
 */
function drush_randlog() {

  // Initialize our options
  $options = randlog_drush_command();
  $options = array_keys($options['randlog']['options']);
  $options = drupal_map_assoc($options);
  foreach ($options AS $option) {
    $options[$option] = drush_get_option($option);
  }

  $main = db_select('users', 'u');
  $main->fields('u', array('name'))
        ->range(1,1)
        ->condition('u.status', 1)
        ->orderBy('RAND()');

  // Subqueries for including and/or excluding roles
  foreach (array('not-' => 'NOT ', '' => '') AS $var => $operator) {
    if (isset($options[$var . 'roles'])) {
      $roles = explode(',', $options[$var . 'roles']);
      $sub = randlog_subquery($roles);
      $main->condition('u.uid', $sub, $operator . 'IN');
    }
  }
  $user = $main->execute()->fetchField(0);
  return drush_user_login($user, $options['path']);
}


/**
 * Create a query object for in/excluding roles
 *
 * @param $roles
 *   Array of role names
 *
 * @return
 *   Object query
 */
function randlog_subquery($roles) {
  $sub = db_select('users_roles', 'ur');
  $sub->join('role', 'r', 'ur.rid = r.rid');
  $sub->fields('ur', array('uid'));
  $sub->condition('r.name', $roles, 'IN');
  return $sub;
}