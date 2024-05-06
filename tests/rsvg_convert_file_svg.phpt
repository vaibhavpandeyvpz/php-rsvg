--TEST--
rsvg_convert_file SVG test
--FILE--
<?php
var_dump(rsvg_convert_file('qrcode.svg', 'qrcode.svg', 'svg', '#ffffff'));

?>
--EXPECT--
bool(true)
