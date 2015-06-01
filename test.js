var addon = require('bindings')('iso8583');
var ISO8583 = addon.ISO8583;
var iso8583 = new ISO8583();

var packedMessage;

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
    iso8583.dump();
    packedMessage = iso8583.packSync();
    packedMessage.length.should.equal(72);
    done();
  });
  
  it ('should unpack an ISO 8583 message', function(done) {
    var iso8583 = new ISO8583(packedMessage);
    var fields = iso8583.unpackSync();
/*    fields[0].toString().should.equal('1234');
    fields[2].toString().should.equal('1234567890123456');
    fields[4].toString().should.equal('5699');
    fields[11].toString().should.equal('234');
    fields[39].toString().should.equal('4');
    fields[41].toString().should.equal('12345');
    fields[42].toString().should.equal('678901234');
    fields[125].toString().should.equal('BLAH BLAH');*/
    for (var k in fields)
      console.log(fields[k].toString());
    done();
  });
});
