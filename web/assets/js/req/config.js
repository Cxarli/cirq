require.config({
  baseUrl: 'assets/js',

  shim: {
    utils: {
      deps: [ ]
    },

    Template: {
      deps: [ ],
    },

    CustomGate: {
      deps: [ ],
    },

    Circuit: {
      deps: [ 'utils' ],
      exports: 'Circuit',
    },

    Port: {
      deps: [ ],
      exports: 'Port',
    },

    Gate: {
      deps: [ 'Port', 'utils' ],
      exports: 'Gate',
    },

    Wire: {
      deps: [ 'utils' ],
      exports: 'Wire',
    },

    wireEvents: {
      deps: [ 'Wire' ],
    },

    dragAndDropEvents: {
      deps: [ 'Gate', 'Wire', 'utils' ],
    },

    indexx: {
      deps: [ 'dragAndDropEvents', 'Circuit', 'CustomGate', 'wireEvents', 'Wire', 'Gate', 'Template', 'utils' ],
    },
  },
});
