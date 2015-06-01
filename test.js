var addon = require('bindings')('iso8583');

describe('ISO 8583 message packing and unpacking', function(){
  it ('should pack an ISO 8583 message', function(done) {
    addon.hello();
    done();
  });
});
