## Javagc and Sac Datasets
`javagc` and `sac` instances are too large for github to store online, so the two instances are respectively separated into 20 parts using 

```shell
./sep.sh javagc
./sep.sh sac
```

To restore the original files, run

```shell
./combine.sh javagc
./combine.sh sac
```
