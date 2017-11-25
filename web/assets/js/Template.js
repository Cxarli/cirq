function Template(html) {
  this.html = html;
}


Template.prototype.apply = function(values) {
  let html = this.html;

  for(let k in values) {
    if (Object.hasOwnProperty(k)) continue;

    let v = values[k];

    html = html.replace(new RegExp('{{\\s*' + k + '\\s*}}', 'gi'), v);
  }

  return html;
};

define(() => Template);
