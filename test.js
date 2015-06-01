var addon = require('bindings')('iso8583');
var ISO8583 = addon.ISO8583;
var iso8583 = new ISO8583();

describe('ISO 8583 message packing and unpacking', function(){
  it ('should pack an ISO 8583 message', function(done) {
    iso8583.packSync();
    done();
  });
});
