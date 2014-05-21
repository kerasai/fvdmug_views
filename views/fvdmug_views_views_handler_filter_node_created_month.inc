<?php

/**
 * @file
 * Views handler for filtering nodes by month created.
 */
class fvdmug_views_views_handler_filter_node_created_month extends views_handler_filter {

  // Just a place to hold an array of months.
  var $months;

  public function construct() {
    parent::construct();
    for ($k = 1; $k <= 12; $k++) {
      $this->months[$k] = date('F', strtotime("2014-$k-01"));
    }
  }

  /**
   * Define options the handler will use.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['value'] = array('default' => array());
    return $options;
  }

  /**
   * The special sauce for defining a filter.
   * 
   * This adds the 'value' element into the options/settings form for the value
   * on which to filter by. This is also used by the exposed form.
   */
  public function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Months'),
      '#options' => $this->months,
      '#default_value' => $this->options['value'],
      '#multiple' => TRUE,
    );
  }

  /**
   * Display the filter on the administrative summary.
   */
  public function admin_summary() {
    return 'IN ' . check_plain(implode(', ', array_intersect_key($this->months, array_flip($this->value))));
  }

  /**
   * Adjust the query to filter per our configuration.
   */
  public function query() {

    // If no months selected, there's nothing for us to do.
    if (!$this->value) {
      return;
    }

    // For filtering on a normal "field" we can use the add_where method of
    // $this->query property. Since we are filtering on the result of a complex
    // formula/expression, we use the add_where_expression method instead.
    $placeholder = $this->placeholder();
    $expression = "MONTH(FROM_UNIXTIME(node.created)) IN ($placeholder)";
    $this->ensure_my_table();
    $this->query->add_where_expression($this->options['group'], $expression, array($placeholder => $this->value));
  }

}
