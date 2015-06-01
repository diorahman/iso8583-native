var addon = require('bindings')('iso8583');
var ISO8583 = addon.ISO8583;
var iso8583 = new ISO8583();

describe('ISO 8583 message packing and unpacking', function(){
  it ('should pack an ISO 8583 message', function(done) {
    var iso8583 = new ISO8583();
    iso8583.setField(0, '1234');
    iso8583.setField(2, '1234567890123456');
    iso8583.setField(4, '5699');
    iso8583.setField(11, '234');
    iso8583.setField(39, '4');
    iso8583.setField(41, '12345');
    iso8583.setField(42, '678901234');
    iso8583.setField(125, 'BLAH BLAH');
    var packedSize = iso8583.packSync();
    packedSize.should.equal(72);
    done();
  });
});
