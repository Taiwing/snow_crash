#!/usr/bin/php
<?php
function y($m) { print "\nWOO@OO\n"; print "\nINPUT_START\n$m\nINPUT_END\n"; $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); print "\nOUTPUT_START\n$m\nOUTPUT_END\n"; return $m; }
function x($y, $z) { print "\nHOLLA\n"; $a = file_get_contents($y); print "\n1\n"; $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); print "\n2\n"; $a = preg_replace("/\[/", "(", $a); print "\n3\n"; $a = preg_replace("/\]/", ")", $a); print "\n4\n"; return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
