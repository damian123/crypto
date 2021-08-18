# Create and import a custom CA (Certificate Authority) and self-signed certificates

## Requirements

Install OpenSSL in powershell
`choco install openssl`

check where openssl is installed by typing
`where openssl`
which should output
`C:\Program Files\OpenSSL-Win64\bin\openssl.exe`

print the openssl version 
`openssl version`
output
`OpenSSL 1.1.1k  25 Mar 2021`

## Output files

| File                  | Description                      |
| --------------------- | -------------------------------- |
| `xyzCA.crt`           | Certificate                      | 
| `xyzCA.pem`           | Certificate                      |
| `xyzCA.key`           | Private key                      |
| `xyzCA.srl`            | Serial                          |
|                                                          |
| `<domainName>.pfx`    | Keystore pfx                     |
| `<domainName>.pkcs12` | Keystore pkcs12                  |
| `<domainName>.crt`    | Certificate                      |
| `<domainName>.csr`    | Certificate Signing Request      |
| `<domainName>.key`    | Private key                      |
| `<domainName>.bundle` | `<domainName>.crt` + `xyzCA.crt` |

## Create your own Certificate Authority (CA)

Edit the `create-ca.bat` file with your data.

```bat
set CompanyName="XYZ Corporation"
set Country="US"
set State="New York"
set Locale="New York"
```

Execute the batch file which will create the private CA key, and generate a root certificate. Please not that you will be promoted to give a pass phrase when executing the command. It is recommneded to enter a password and secure your private keyin a secure vault or Hardware Security Module (HSM).
```bat
create-ca.bat <domainName>
create-ca.bat xyz.corp
```

## Creating a certificate signed by your own CA

Edit the `create-cert.bat` file with your data.

```bat
set CompanyName="XYZ Corporation"
set Country="US"
set State="New York"
set Locale="New York"
```

Generate the Certificate that is valid for 1 year. Note that we need to use the CA's root cerficiate and the private key we just generated in the prior step. We need to enter the CA private key's password when promoted and an export password which the pass phrase for the <domainName>.key private key

```bat
create-cert.bat <domainName> <alternativeName>
create-cert.bat headquarters.xyz.corp hq.xyz.corp
```

## Import the certificates

Import the CA:
```bat
import-ca.bat ca-certificate\xyzCA.crt
```

You can verify that the cerficate was import by running  Certmgr.msc in the Trusted Root Certification Autorities\Cerficates folder where you can find a CA issued xyz.corp at the end of the list.

Import the certifcate signed by your own CA
```
CertUtil -f -p "<PASSWORD>"" -importpfx certificate\certificates\headquarters.xyz.corp_keystore.pfx
```

# Sign the .xll

```
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.17763.0\x64\signtool" sign /f d:\dev\trading\crypto\cpp\src\adaptors\xll\cert\certificates\headquarters.xyz.corp_keystore.pfx /p "<PASSWORD>" D:\dev\trading\crypto\build\cpp\src\adaptors\xll\Release\cryptoXL.xll
```
This will output
```
Done Adding Additional Store
Successfully signed: D:\dev\trading\crypto\build\cpp\src\adaptors\xll\Release\cryptoXL.xll
```
TODO: Describe the deployment on a client PC, i.e. import the CA's public key and accept the warning the first time in Excel.
