;(function($) {
  Drupal.behaviors.trainingOnLoad = {
    attach: function(context) {
      console.log('Here (behavior)');
      if (Drupal.settings.user_id){
        console.log(Drupal.settings.random_num);
        console.log(Drupal.settings.user_id);
        console.log(Drupal.t('User ID = !id', {'!id': Drupal.settings.user_id}));
      }
    }
  };
  console.log(Drupal.ajax);
  if (Drupal.ajax) {
    Drupal.ajax.prototype.commands.reload = function(ajax, data, status) {
      console.log('hello!');
      console.log(data);
    };
  }
})(jQuery)
