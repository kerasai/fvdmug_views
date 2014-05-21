<?php

/**
 * @file
 * Views handler for dsiplaying month created for nodes.
 */
class fvdmug_views_views_handler_field_node_created_month extends views_handler_field {

  /**
   * Define options the handler will use.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['display'] = array('default' => 'full');
    return $options;
  }

  /**
   * Provide a form so a user can manipulate the options.
   * 
   * Vaidate and submit callbacks/methods also available.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['display'] = array(
      '#type' => 'select',
      '#title' => t('Display'),
      '#options' => array(
        'num' => t('Numeric'),
        'abbr' => t('Abbreviation'),
        'full' => t('Full Month'),
      ),
      '#default_value' => $this->options['display'],
    );
  }

  /**
   * Override the normal query method with our formula.
   * 
   * This is likely not compatible for all SQL databases, only tested in MySQL.
   */
  public function query() {
    $formula = 'MONTH(FROM_UNIXTIME(node.created))';
    $this->field_alias = $this->query->add_field(NULL, $formula, 'node_created_month');
    $this->aliases['node_created_month'] = $this->field_alias;
  }

  /**
   * Render the value for each row.
   */
  public function render($values) {
    $month = $this->get_value($values, 'node_created_month');

    // Adjust the format based on configured options.
    switch ($this->options['display']) {
      case 'abbr':
        $month = date('M', strtotime("2014-$month-01"));
        break;
      case 'full':
        $month = date('F', strtotime("2014-$month-01"));
        break;
    }

    return check_plain($month);
  }

}
