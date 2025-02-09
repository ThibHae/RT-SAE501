sudo apt update
sudo apt install open-vm-tools open-vm-tools-desktop -y
sudo apt upgrade -y
sudo apt install openssh-server vlc git make gcc curl cmake -y
sudo apt install autoconf automake build-essential ccache cmake cpufrequtils doxygen ethtool g++ git inetutils-tools libboost-all-dev libncurses5 libncurses5-dev libusb-1.0-0 libusb-1.0-0-dev libusb-dev python3-dev python3-mako python3-numpy python3-requests python3-scipy python3-setuptools python3-ruamel.yaml
unzip uhd-4.6.0.0.zip && mv uhd-4.6.0.0 /home/$USER/uhd
cd /home/$USER/uhd; mkdir host/build; cd host/build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make -j4
sudo make install
sudo ldconfig
sudo /usr/lib/uhd/utils/uhd_images_downloader.py
sudo cp /usr/lib/uhd/utils/uhd-usrp.rules /etc/udev/rules.d/10-uhd-usrp.rules
reebot
cd ~
wget https://open-cells.com/opencells-mods-20190923.tgz
tar xf opencells-mods-20190923.tgz
wget https://open-cells.com/d5138782a8739209ec5760865b1e53b0/openair-cn.tgz
tar xvf openair-cn.tgz
cd openair-cn
git checkout develop
git apply ~/opencells-mods/EPC.patch
source oaienv; cd scripts
./build_hss -i
sudo mysql -u root << END
USE mysql;
UPDATE user SET plugin='mysql_native_password' WHERE User='root';
FLUSH PRIVILEGES;
END
sudo systemctl restart mysql.service
sudo mysql_secure_installation
./build_mme -i
sudo adduser $USER wireshark
reboot
cd openair-cn; source oaienv; cd scripts
./build_spgw -i
cd
cd openair-cn; source oaienv; cd scripts
./build_hss
./build_mme
./build_spgw
cd
sudo mkdir -p /usr/local/etc/oai
sudo cp -rp ~/opencells-mods/config_epc/* /usr/local/etc/oai
sudo openair-cn; source oaienv; cd scripts
./check_hss_s6a_certificate /usr/local/etc/oai/freeDiameter hss.OpenAir5G.Alliance
./check_hss_s6a_certificate /usr/local/etc/oai/freeDiameter mme.OpenAir5G.Alliance
ip a
sudo nano /usr/local/etc/oai/spgw.conf
sudo nano /usr/local/etc/oai/mme.conf
sudo nano /usr/local/etc/oai/hss.conf
~/opencells-mods/hss_import 127.0.0.1 root rt1234 oai_db ~/opencells-mods/opencells_db.sql
cd
git clone https://gitlab.eurecom.fr/oai/openairinterface5g.git
cd openairinterface5g
git reset --hard edb74831dabf79686eb5a92fbf8fc06e6b267d35
source oaienv
./cmake_targets/build_oai -I
./cmake_targets/build_oai -h
./cmake_targets/build_oai -w USRP --eNB --UE --build-lib all
sudo nano ~/opencells-mods/enb.10MHz.b200
cd
cd openair-cn; source oaienv; cd scripts; ./run_hss
cd
cd openair-cn; source oaienv; cd scripts; ./run_mme
cd
cd openair-cn; source oaienv; cd scripts; sudo -E ./run_spgw
nano ~/opencells-mods/enb.10MHz.b200
sudo uhd_usrp_probe
sudo bash
cd ~/openairinterface5g; source oaienv
cd cmake_targets/lte_build_oai/build
./lte-softmodem -O ~/opencells-mods/enb10MHz.b200 -d
