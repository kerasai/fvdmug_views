<?php

/**
 * @file
 * Views handler for displaying a link to a node's devel page.
 */
class fvdmug_views_views_handler_field_node_devel_link extends views_handler_field {

  public function render($values) {
    if (user_access('access devel information')) {
      $nid = $this->get_value($values);
      return l(t('Devel'), "node/$nid/devel");
    }
  }

}
