--TEST--
tcpwrap_check()
--SKIPIF--
<?php if (!extension_loaded("tcpwrap")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php 
$r = tcpwrap_check('foo', '127.0.0.1');
echo gettype($r);
?>
--EXPECT--
boolean
