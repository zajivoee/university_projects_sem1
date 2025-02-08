Домашние задачи для курса МИФИ "Архитектура компьютера и операционных систем".

## Клонируем репозиторий

```bash
# Переходим в директорию, где вы хотите разместить репозиторий с задачами.
# Например, `/home/<username>/mephi/os` для Linux или `/Users/<username>/mephi/os` для MacOS.
$ cd <выбранная директория>

# Клонируем свой репозиторий, который создается автоматически при регистрации на manytask.
# Имя репозитория доступно по ссылке "MY REPO" на mephi-dap-os.manytask.org.
$ git clone https://gitlab.manytask.org/mephi-dap-os/students-2024-2025/<ваш login с mephi-dap-os.manytask.org>.git

# Переходим в директорию склонированного репозитория.
$ cd <ваш репозиторий>

# Настраиваем свое имя в git.
$ git config --local user.name "<ваш login с mephi-dap-os.manytask.org>"
$ git config --local user.email "<ваш email с mephi-dap-os.manytask.org>"

# По дефолту просим git запускать команду rebase для подтягивания конфликтующих изменений.
$ git config --local pull.rebase true

# Настраиваем возможность получать обновления при появлении новых задач.
$ git remote add upstream https://gitlab.manytask.org/mephi-dap-os/public-2024-2025.git
```

## Подтягиваем новые задачи

Периодически необходимо подтягивать изменения из основного репозитория с задачками: https://gitlab.manytask.org/mephi-dap-os/public-2024-2025. Например, когда появляются новые задачки или меняются условия старых.

```bash
$ git pull upstream main
```

Если старые задачи менялись, при подтягивании изменений возможен конфликт ваших локальных изменений и новых изменений от преподавателей. Для разрешения конфликта предлагается:
```bash
# Показать файлы с конфликтами.
$ git status

$ ... разрешение конфликта в каждом из файлов ...

# Сообщаем git для каждого файла, что конфликт разрешен.
$ git add <файл с конфликтом>

# Продолжаем подтягивание изменений.
# После выполнения команды последующие изменения могут опять создать конфликт и процедуру разрешения конфликта придется повторить.
$ git rebase --continue
```

Когда убедились, что изменения корректно применились, пушим их в репозиторий:
```bash
$ git push -f
```

Если послать решение задачи вместе с изменениями от rebase, то тестирующая система не сможет определить список решенных задач, потому что rebase полностью переписывает историю. В такой ситуации предлагается поменять свое решение любым образом (например, добавив лишнюю пустую строку) и послать решение еще раз.

## Решаем задачи

В каждой из папок находится условие и файлы очередной задачи.

Файлы main.cpp и makefile в каждой задаче отвечают за тестирование. При проверке решения они перезаписываются, так что их изменения не учитываются.

Остальные файлы менять можно и нужно.

Для тестирования в каждой задаче достаточно вызвать:
```bash
$ make
```

Команда соберет бинарные файлы из исходных и запустит тесты в main.cpp.

Как только убедились, что решение работает, отправить его можно коммитом в репозиторний:
```bash
$ git add <измененный файл>
$ git commit -m "<комментарий, описывающий изменения>"
$ git push origin main
```

Процесс проверки автоматизирован, результаты проверки можно увидеть либо в CI/CD коммита (зеленая/красная/желтая галочка напротив коммита), либо во вкладках SUBMITS и GDOC главной страницы курса https://mephi-dap-os.manytask.org/.

Закрытых тестов в задачах нет, все тесты публичные и доступны в main.cpp. Сообщения, записанные в консоль в процессе тестирования, можно увидеть в результатах проверки.

## Запуск в Docker

Если у вас нет OS Linux или x86_64 процессора, то вы можете воспользоваться Docker

1) [Скачать](https://www.docker.com/products/docker-desktop/) приложение докера.

2) Создаем образ `mephi-os` (требуется сделать всего один раз):
```bash
cd <ваш репозиторий>
docker build --platform linux/x86_64 . -t mephi-os
```

3) После того как вы создали образ `mephi-os`. Можно создать контейнер:
```bash
docker run --platform linux/x86_64 -it --rm -v <путь до вашего репозитория>:/workspace mephi-os bash
```

Эта команда переключает вас в контейнер в интерактивном режиме, а так же синхронизирует вашу текущую директорию с директорией `/workspace` в контейнере. Вы можете менять файлы как в контейнере, так и вне, все изменения будут видны в обоих местах.
В контейнере можно запускать код с помощью команды make, а так же тестировать с помощью gdb.

## Запуск gdb на не x86_64 архитектурах

1) Запуститься в докере

2) Запустить бинарник `main` в эмуляторе qemu в фоновом режиме
```bash
qemu-x86_64-static -g 1234 main &
```

3) Подключится в gdb
```bash
gdb main
...
(gdb) target remote localhost:1234
```

Ваш бинарник уже запущен, можно начинать дебажить.

## Codestyle

Рекомендуем пользоваться https://ysda.gitlab.io/algorithms/styleguide.html
