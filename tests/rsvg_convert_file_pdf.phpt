--TEST--
rsvg_convert_file PDF test
--FILE--
<?php
var_dump(rsvg_convert_file('qrcode.svg', 'qrcode.pdf', 'pdf'));

?>
--EXPECT--
bool(true)
