<?php


function dw_tools_default_rules_configuration() {

  $configs = array();

  // Reserve stock when the user has added a product to their cart.
  $rule = rules_reaction_rule();
  $rule->label = 'Reserve stock when a user adds a product to their cart';
  $rule->active = TRUE;
  $rule->tags = array('commerce_stock_reserve', 'stock_control');
  $rule->event('commerce_cart_product_add');
  $rule->condition('data_is', array(
      'data:select' => 'commerce-order:state',
      'op' => '==',
      'value' => 'cart',
  ));
  $rule->action('commerce_stock_reserve_reserve', array(
      'commerce_line_item:select' => 'commerce-line-item',
  ));
  $configs['commerce_stock_reserve_for_cart'] = $rule;
  
  

  // Reserve stock when the user has updated a product in their cart.
  $rule = rules_reaction_rule();
  $rule->label = 'Reserve stock when a user updates a product in their cart';
  $rule->active = TRUE;
  $rule->tags = array('commerce_stock_reserve', 'stock_control');
  $rule->event('commerce_line_item_update');
  $rule->condition('data_is', array(
      'data:select' => 'commerce-line-item:order:state',
      'op' => '==',
      'value' => 'cart',
  ));
  $rule->action('commerce_stock_reserve_reserve', array(
      'commerce_line_item:select' => 'commerce-line-item',
  ));
  $configs['commerce_stock_reserve_cart_update'] = $rule;

  // Release stock when the user has removed a product from their cart.
  $rule = rules_reaction_rule();
  $rule->label = 'Release reserved stock for cart';
  $rule->active = TRUE;
  $rule->tags = array('commerce_stock_reserve', 'stock_control');
  $rule->event('commerce_cart_product_remove');
  $rule->action('commerce_stock_reserve_release', array(
      'commerce_line_item:select' => 'commerce-line-item',
  ));
  $configs['commerce_stock_reserve_release_for_cart'] = $rule;

  // Release stock when the user completes checkout for an order.
  $rule = rules_reaction_rule();
  $rule->label = 'Release reserved stock when completing checkout';
  $rule->active = TRUE;
  $rule->tags = array('commerce_stock_reserve', 'stock_control');
  $rule->event('commerce_checkout_complete');
  $rule->action(
      rules_loop(array(
          'list:select' => 'commerce-order:commerce-line-items',
          'item:var' => 'line_item',
          'item:label' => t('Current line item'),
          'item:type' => 'commerce_line_item',
      ))
      ->action('commerce_stock_reserve_release', array(
          'commerce_line_item:select' => 'line-item',
      ))
  );
  $configs['commerce_stock_reserve_release_checkout'] = $rule;

  // Release reserved stock for canceled orders.
  $rule = rules_reaction_rule();
  $rule->label = 'Release reserved stock for canceled orders';
  $rule->active = TRUE;
  $rule->tags = array('commerce_stock_reserve', 'stock_control');
  $rule->event('commerce_order_update');
  // Check that the order is now in a 'canceled' state, when it was previously
  // in a 'cart' or 'checkout' state.
  $rule->condition('data_is', array(
      'data:select' => 'commerce-order:state',
      'value' => 'canceled',
  ))
  ->condition('data_is', array(
      'data:select' => 'commerce-order-unchanged:state',
      'op' => 'IN',
      'value' => array(
          'cart' => 'cart',
          'checkout' => 'checkout',
      ),
  ));
  // Release stock for the order's line items.
  $rule->action(
      rules_loop(array(
          'list:select' => 'commerce-order:commerce-line-items',
          'item:var' => 'line_item',
          'item:label' => t('Current line item'),
          'item:type' => 'commerce_line_item',
      ))
      ->action('commerce_stock_reserve_release', array(
          'commerce_line_item:select' => 'line-item',
      ))
  );
  $configs['commerce_stock_reserve_release_canceled'] = $rule;

  return $configs;
}

/*
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
*/
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