require.config({
  baseUrl: 'assets/js',

  shim: {
    utils: {
      deps: [ ]
    },

    CustomGate: {
      deps: [ ],
    },

    Template: {
      deps: [ 'utils' ],
    },

    Circuit: {
      deps: [ 'utils' ],
      exports: 'Circuit',
    },

    Wire: {
      deps: [ 'utils' ],
      exports: 'Wire',
    },

    Port: {
      deps: [ 'Wire' ],
      exports: 'Port',
    },

    Gate: {
      deps: [ 'Port', 'utils' ],
      exports: 'Gate',
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
