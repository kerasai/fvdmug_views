<?php

/**
 * @file
 * FVDMUG Views Demo Views integration code.
 */

/**
 * Implements hook_views_data_alter().
 * 
 * Make adjustments to the Views integration for tables provided by other 
 * modules.
 */
function fvdmug_views_views_data_alter(&$data) {

  // To see the full listing, make sure devel is enabled and uncomment the line 
  // below.
  //dpm($data, __FUNCTION__);
  // Provide a link to a node's devel page.
  if (module_exists('devel')) {
    $data['node']['devel_link'] = array(
      'real field' => 'nid',
      'field' => array(
        'title' => t('Devel link'),
        'help' => t('Provide a simple link to a node\'s Devel page.'),
        'handler' => 'fvdmug_views_views_handler_field_node_devel_link',
      ),
    );
  }

  // Node creation month.
  $data['node']['created_month']['field'] = array(
    'handler' => 'fvdmug_views_views_handler_field_node_created_month',
    'click sortable' => TRUE,
  );
  $data['node']['created_month']['filter'] = array(
    'handler' => 'fvdmug_views_views_handler_filter_node_created_month',
  );
}
