/* global LOOP_OBJ */


function Template(html) {
  this.html = html;
}


Template.prototype.apply = function(values) {
  let html = this.html;

  // Apply all values
  LOOP_OBJ(values).forEach((k, v) => {
    html = html.replace(new RegExp('{{\\s*' + k + '\\s*}}', 'gi'), v);
  });

  return html;
};


define(() => Template);
