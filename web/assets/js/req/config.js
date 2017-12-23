/* globals require */

require.config({
    baseUrl: 'assets/js',

    shim: {
        utils: {
            deps: [ ]
        },

        CustomGate: {
            deps: [ 'utils' ],
            exports: 'CustomGate',
        },

        Template: {
            deps: [ 'utils' ],
            exports: 'Template',
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
            deps: [ 'dragAndDropEvents', 'wireEvents', 'Circuit', 'CustomGate', 'Template', 'utils', 'Wire', 'Gate' ],
        },
    },
});
