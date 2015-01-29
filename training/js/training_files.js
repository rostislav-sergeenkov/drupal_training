;(function($) {
  Drupal.behaviors.trainingTableFileOnLoad = {
    attach: function(context) {
      if (Drupal.settings.user_id) {
        for (var key in Drupal.settings.array_id) {
          var val = Drupal.settings.array_id [key];
          if (val == Drupal.settings.user_id) {
            $('#fid-cell-' + key).css('background-color','#b8faff');
          }
        }
      }
    }
  };
})(jQuery)
