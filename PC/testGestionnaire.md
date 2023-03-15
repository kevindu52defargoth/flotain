# test du gestionnaire

Compiler le gestionnaire, et le programme de test :
```bash
gcc gestionnaire.c testGestionnaire.c -o gestionnaire -I . -L . -l inet
```

Faire tourner le gestionnaire :
```bash
./gestionnaire
```

Dans un autre terminal, on peut contacter le serveur sur localhost, port 9091 :
```bash
nc 0.0.0.0 9092
```

Il y a 4 ressources,
* T*i* prend la ressource *i*

* L*i* rend la ressource *i*

* autre chose ferme la connection

[![](https://mermaid.ink/img/pako:eNptjj0LwjAYhP9KeFfbwTVDQRQcHAR1zPKSnBraJDUfg5T-dyOl4OBNx91zcBPpYECSEl4FXuNg-RHZKS-q9oOFz23XbY5I2Qbv2UZIcdsu_W9aqQWXYqf7v327AueTuCClUKIGNeQQHVtTX0zfnaL8hIMiWa3h2CtSfq4clxyub69J5ljQUBkN5_UxyTsPCfMH9p9Gzg?type=png)]
