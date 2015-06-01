// Compares some libs from net.

// It turns out the example from [1] uses 1987 standard
// [1] http://jpos.org/products/iso_c_lib

var addon = require('bindings')('iso8583');
var ISO8583 = addon.ISO8583;
var iso8583 = new ISO8583();
iso8583.use1987();
iso8583.setField(0, '0080');
iso8583.setField(2, '454000000000003');
iso8583.setField(3, '000000');
iso8583.setField(28, 'C1200');
iso8583.setField(11, '000001');
iso8583.setField(34, '12345');
iso8583.setField(41, '12345678');
iso8583.setField(70, '301');
iso8583.dump();
var packed = iso8583.packSync();
iso8583.outputHex();

console.log();
console.log('packed length', packed.length);
console.log();

var iso = new ISO8583(packed);
iso.use1987();
var fields = iso.unpackSync();
for (var k in fields) {
  console.log(k, fields[k].toString());
}
