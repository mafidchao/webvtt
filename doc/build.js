var mdoc = require('mdoc');

mdoc.run({

    // === required settings === //

    inputDir : 'api',
    outputDir : 'doc',

    // === optional settings === //

    baseTitle : 'WebVTT parser',
    indexContentPath : 'index.mdown'

});
