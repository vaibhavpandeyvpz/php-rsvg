--TEST--
rsvg_convert stress test
--FILE--
<?php

$format1 = 'eps';
$format2 = 'png';
$format3 = 'pdf';
$format4 = 'svg';

for ($i = 0; $i < 100; $i++) {
    rsvg_convert(file_get_contents('qrcode.svg'), $format1);
    rsvg_convert(file_get_contents('qrcode.svg'), $format2);
    rsvg_convert(file_get_contents('qrcode.svg'), $format3);
    rsvg_convert(file_get_contents('qrcode.svg'), $format4);
}

?>
--EXPECT--
