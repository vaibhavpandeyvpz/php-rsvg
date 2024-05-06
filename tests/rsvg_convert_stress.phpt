--TEST--
rsvg_convert stress test
--FILE--
<?php
for ($i = 0; $i < 100; $i++) {
    rsvg_convert(file_get_contents('qrcode.svg'), 'eps');
    rsvg_convert(file_get_contents('qrcode.svg'), 'png');
    rsvg_convert(file_get_contents('qrcode.svg'), 'pdf');
    rsvg_convert(file_get_contents('qrcode.svg'), 'svg');
}

?>
--EXPECT--
