
# Dining Philosophers

### A Classic Problem - Dining Philosophers
The Dining Philosophers problem is a classic OS problem that’s usually stated in very non-OS terms:
There are N philosphers sitting around a circular table eating spaghetti and discussing philos-
phy. The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one
between each 2 philosophers. Design an algorithm that the philosophers can follow that
insures that none starves as long as each philosopher eventually stops eating, and such that the
maximum number of philosophers can eat at once

One or more philosophers are sitting at a round table either eating, either thinking,
either sleeping. While they are eating, they do not think or sleep; while thinking
they don’t eat or sleep; and, of course, while sleeping, they do not eat or think


## Acknowledgements

 - [A Classic Problem - Dining Philosophers (PDF)](https://www.ecb.torontomu.ca/~courses/coe518/Labs/lab4/lisi.edu-dining-Philosopherecture8.pdf)
 - [Philosophers problem solving (Youtube)](https://www.youtube.com/watch?v=9f1oOMX3mP4&t=230s)
 - [42-school philosophers project (Youtube (ru))](https://www.youtube.com/watch?v=WzsPbwIwtiw&t=4808s)


<p align="center">
  <img src="https://github.com/davitMartirosyan/42-yerevan-philosophers/blob/master/philos.png?raw=true"/>
</p>

## Instalation

To run philosophers try to make first all object files

```
  make
```
After that try to run philosophers
```
./philo [N] [time_to_die] [time_to_eat] [time_to_sleep] [optional_must_eat]
```

example:
```
./philo 5 800 200 200 7
```
