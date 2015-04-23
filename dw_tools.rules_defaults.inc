<?php



function dw_tools_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = t('Highlight user logged in as admin"');
  $rule->active = TRUE;

  $rule
  ->event('node_view')
  ->condition(
      rules_condition('user_has_role', array(
          'account:select' => 'site:current-user',
          'roles' => array(3),
          'operation' => 'AND'
      )
      )
  )
  ->action(
      'drupal_message',
      array(
          'message' => 'You are currently logged in as the administrative user!',
          'type' => 'warning',
          'repeat' => FALSE,
      )
  );

  $rules['highlight_user_is_admin'] = $rule;

  return $rules;
}

/*
 { "highlight_user_is_admin" : {
    "LABEL" : "Highlight user logged in as admin\u0022",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "rules" ],
    "ON" : { "node_view" : [] },
    "IF" : [
      { "user_has_role" : { "account" : [ "site:current-user" ], "roles" : { "value" : [ 3 ] } } }
    ],
    "DO" : [
      { "drupal_message" : {
          "message" : "You are currently logged in as the administrative user!",
          "type" : "warning",
          "repeat" : false
        }
      }
    ]
  }
}*/