# MiniFab

## Installation

**REQUIREMENTS:**
- [WiringPi](http://wiringpi.com/download-and-install/)

First, move the folder "minifab" into your user directory "/home/\<user\>/"

These next steps will allow MiniFab service to load on each startup.

```bash
sudo vim /etc/systemd/system/minifab.service
```

Fill in these lines (replace *\<user\>* by your user name)

```
[Unit]
Description=MiniFab service startup
After=network.target

[Service]
Type=simple
ExecStart=/home/<user>/minifab/startup.sh
TimeoutStartSec=0

[Install]
WantedBy=default.target
```
Enter **:qw** to save and exit.\
Then

```bash
sudo systemctl daemon-reload
sudo systemctl enable minifab.service
```

Tadam.
