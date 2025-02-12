## Компиляция

```bash
make
```
## Загрузка модуля

```bash
sudo insmod custom_device.ko
```

## Проверка работы

```bash
ls /dev/custom_device
cat /proc/custom_device_info
cat /sys/class/custom_device/custom_attr
echo 1 | sudo tee /sys/class/custom_device/custom_attr
```

## Удаление модуля

```bash
sudo rmmod custom_device
```