#define R_REGISTER 0x00
#define W_REGISTER 0x20
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2
#define REUSE_TX_PL 0xE3
#define R_RX_PL_WID 0x60 
#define W_ACK_PAYLOAD 0xA8 
#define W_TX_PAYLOAD_NOACK 0xB0
#define NOP 0xFF


#define CONFIG 0x00
#define EN_AA  0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07 
#define OBSERVE_TX 0x08
#define RPD 0x09 
#define RX_ADDR_P0 0x0A 
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D


/* Биты регистров */

// CONFIG
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0

// EN_AA
#define ENAA_P5 5
#define ENAA_P4 4
#define ENAA_P3 3
#define ENAA_P2 2
#define ENAA_P1 1
#define ENAA_P0 0

// EN_RXADDR
#define ERX_P5 5
#define ERX_P4 4
#define ERX_P3 3
#define ERX_P2 2
#define ERX_P1 1 
#define ERX_P0 0 

// SETUP_AW
#define AW 0

#define SETUP_AW_3BYTES_ADDRESS (1 << AW)
#define SETUP_AW_4BYTES_ADDRESS (2 << AW)
#define SETUP_AW_5BYTES_ADDRESS (3 << AW)

// SETUP_RETR 
#define ARD 4
#define ARC 0

#define SETUP_RETR_DELAY_250MKS  (0 << ARD)
#define SETUP_RETR_DELAY_500MKS  (1 << ARD)
#define SETUP_RETR_DELAY_750MKS  (2 << ARD)
#define SETUP_RETR_DELAY_1000MKS (3 << ARD)
#define SETUP_RETR_DELAY_1250MKS (4 << ARD)
#define SETUP_RETR_DELAY_1500MKS (5 << ARD)
#define SETUP_RETR_DELAY_1750MKS (6 << ARD)
#define SETUP_RETR_DELAY_2000MKS (7 << ARD)
#define SETUP_RETR_DELAY_2250MKS (8 << ARD)
#define SETUP_RETR_DELAY_2500MKS (9 << ARD)
#define SETUP_RETR_DELAY_2750MKS (10 << ARD)
#define SETUP_RETR_DELAY_3000MKS (11 << ARD)
#define SETUP_RETR_DELAY_3250MKS (12 << ARD)
#define SETUP_RETR_DELAY_3500MKS (13 << ARD)
#define SETUP_RETR_DELAY_3750MKS (14 << ARD)
#define SETUP_RETR_DELAY_4000MKS (15 << ARD)

#define SETUP_RETR_NO_RETRANSMIT (0 << ARC)
#define SETUP_RETR_UP_TO_1_RETRANSMIT (1 << ARC)
#define SETUP_RETR_UP_TO_2_RETRANSMIT (2 << ARC)
#define SETUP_RETR_UP_TO_3_RETRANSMIT (3 << ARC)
#define SETUP_RETR_UP_TO_4_RETRANSMIT (4 << ARC)
#define SETUP_RETR_UP_TO_5_RETRANSMIT (5 << ARC)
#define SETUP_RETR_UP_TO_6_RETRANSMIT (6 << ARC)
#define SETUP_RETR_UP_TO_7_RETRANSMIT (7 << ARC)
#define SETUP_RETR_UP_TO_8_RETRANSMIT (8 << ARC)
#define SETUP_RETR_UP_TO_9_RETRANSMIT (9 << ARC)
#define SETUP_RETR_UP_TO_10_RETRANSMIT (10 << ARC)
#define SETUP_RETR_UP_TO_11_RETRANSMIT (11 << ARC)
#define SETUP_RETR_UP_TO_12_RETRANSMIT (12 << ARC)
#define SETUP_RETR_UP_TO_13_RETRANSMIT (13 << ARC)
#define SETUP_RETR_UP_TO_14_RETRANSMIT (14 << ARC)
#define SETUP_RETR_UP_TO_15_RETRANSMIT (15 << ARC)

// RF_SETUP
#define CONT_WAVE 7
#define RF_DR_LOW 5
#define PLL_LOCK 4
#define RF_DR_HIGH 3
#define RF_PWR 1

#define RF_SETUP_MINUS18DBM (0 << RF_PWR)
#define RF_SETUP_MINUS12DBM (1 << RF_PWR)
#define RF_SETUP_MINUS6DBM  (2 << RF_PWR)
#define RF_SETUP_0DBM       (3 << RF_PWR)

#define RF_SETUP_1MBPS (0 << RF_DR_HIGH)
#define RF_SETUP_2MBPS (1 << RF_DR_HIGH)
#define RF_SETUP_250KBPS (1 << RF_DR_LOW)

// STATUS
#define RX_DR 6
#define TX_DS 5
#define MAX_RT 4
#define RX_P_NO 1
#define TX_FULL_STATUS 0

// OBSERVE_TX
#define PLOS_CNT 4
#define ARC_CNT 0 

// FIFO_STATUS
#define TX_REUSE 6 
#define TX_FULL_FIFO 5
        
#define TX_EMPTY 4
#define RX_FULL 1
#define RX_EMPTY 0

// DYNDP
#define DPL_P5 5
#define DPL_P4 4
#define DPL_P3 3
#define DPL_P2 2
#define DPL_P1 1
#define DPL_P0 0

// FEATURE  
#define EN_DPL 2
#define EN_ACK_PAY 1
#define EN_DYN_ACK 0

#define SPI_DDR DDRB
#define SPI_SS 0
#define SPI_MOSI 2
#define SPI_SCK 1

// Инициализация интерфейса
void spi_init() {
  SPI_DDR |= (1 << SPI_MOSI) | (1 <<  SPI_SCK) | (1 << SPI_SS);
  SPCR = (1 << SPE) | (1 << MSTR); // режим 0, мастер, частота 1/4 от частоты ЦП
}

// Передаёт и принимает 1 байт по SPI, возвращает полученное значение
uint8_t spi_send_recv(uint8_t data) {
  SPDR = data;
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}



#define RADIO_PORT PORTD
#define RADIO_DDR DDRD
#define RADIO_PIN PIND

#define RADIO_CSN 3////////////
#define RADIO_CE 6//////////////
#define RADIO_IRQ 2

// Выбирает активное состояние (высокий уровень) на линии CE
inline void radio_assert_ce() {
  RADIO_PORT |= (1 << RADIO_CE); // Установка высокого уровня на линии CE
}

// Выбирает неактивное состояние (низкий уровень) на линии CE
inline void radio_deassert_ce() {
  RADIO_PORT &= ~(1 << RADIO_CE);
}

// Поскольку функции для работы с csn не предполагается использовать в иных файлах, их можно объявить static

// Выбирает активное состояние (низкий уровень) на линии CSN
inline static void csn_assert() {
  RADIO_PORT &= ~(1 << RADIO_CSN);
}

// Выбирает неактивное состояние (высокий уровень) на линии CSN
inline static void csn_deassert() {
  RADIO_PORT |= (1 << RADIO_CSN);
}

// Инициализирует порты 
void radio_init() {
  RADIO_DDR |= (1 << RADIO_CSN) | (1 << RADIO_CE); // Ножки CSN и CE на выход
  RADIO_DDR &= ~(1 < RADIO_IRQ); // IRQ - на вход
  csn_deassert();
  radio_deassert_ce();
  spi_init();
}

// Выполняет команду cmd, и читает count байт ответа, помещая их в буфер buf, возвращает регистр статуса
uint8_t radio_read_buf(uint8_t cmd, uint8_t * buf, uint8_t count) {
  csn_assert();
  uint8_t status = spi_send_recv(cmd);
  while (count--) {
    *(buf++) = spi_send_recv(0xFF);
  }
  csn_deassert();
  return status;
}

// Выполняет команду cmd, и передаёт count байт параметров из буфера buf, возвращает регистр статуса
uint8_t radio_write_buf(uint8_t cmd, uint8_t * buf, uint8_t count) {
  csn_assert();
  uint8_t status = spi_send_recv(cmd);
  while (count--) {
    spi_send_recv(*(buf++));
  }
  csn_deassert();
  return status;
}

// Читает значение однобайтового регистра reg (от 0 до 31) и возвращает его
uint8_t radio_readreg(uint8_t reg) {
  csn_assert();
  spi_send_recv((reg & 31) | R_REGISTER);
  uint8_t answ = spi_send_recv(0xFF);
  csn_deassert();
  return answ;
}

// Записывает значение однобайтового регистра reg (от 0 до 31), возвращает регистр статуса
uint8_t radio_writereg(uint8_t reg, uint8_t val) {
  csn_assert();
  uint8_t status = spi_send_recv((reg & 31) | W_REGISTER);
  spi_send_recv(val);
  csn_deassert();
  return status;
}

// Читает count байт многобайтового регистра reg (от 0 до 31) и сохраняет его в буфер buf,
// возвращает регистр статуса
uint8_t radio_readreg_buf(uint8_t reg, uint8_t * buf, uint8_t count) {
  return radio_read_buf((reg & 31) | R_REGISTER, buf, count);
}

// Записывает count байт из буфера buf в многобайтовый регистр reg (от 0 до 31), возвращает регистр статуса
uint8_t radio_writereg_buf(uint8_t reg, uint8_t * buf, uint8_t count) {
  return radio_write_buf((reg & 31) | W_REGISTER, buf, count);
}

// Возвращает размер данных в начале FIFO очереди приёмника
uint8_t radio_read_rx_payload_width() {
  csn_assert();
  spi_send_recv(R_RX_PL_WID);
  uint8_t answ = spi_send_recv(0xFF);
  csn_deassert();
  return answ;
}

// Выполняет команду. Возвращает регистр статуса
uint8_t radio_cmd(uint8_t cmd) {
  csn_assert();
  uint8_t status = spi_send_recv(cmd);
  csn_deassert();
  return status;
}

// Возвращает 1, если на линии IRQ активный (низкий) уровень.
uint8_t radio_is_interrupt() {
  return (RADIO_PIN & RADIO_IRQ) ? 0 : 1;
}


// Функция производит первоначальную настройку устройства. Возвращает 1, в случае успеха, 0 в случае ошибки
uint8_t radio_start() {
	uint8_t self_addr[] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7}; // Собственный адрес
	uint8_t remote_addr[] = {0x78, 0x78, 0x78, 0x78, 0x78}; // Адрес удалённой стороны
	uint8_t chan = 60; // Номер радио-канала (в диапазоне 0 - 125)

	radio_deassert_ce();
	for(uint8_t cnt = 100;;) {
		radio_writereg(CONFIG, (1 << EN_CRC) | (1 << CRCO) | (1 << PRIM_RX)); // Выключение питания
		if (radio_readreg(CONFIG) == ((1 << EN_CRC) | (1 << CRCO) | (1 << PRIM_RX)))
		break;
		// Если прочитано не то что записано, то значит либо радио-чип ещё инициализируется, либо не работает.
		if (!cnt--)
		return 0; // Если после 100 попыток не удалось записать что нужно, то выходим с ошибкой
		_delay_ms(1);
	}

	radio_writereg(EN_AA, (1 << ENAA_P1) | ( 1<< ENAA_P0)); // включение автоподтверждения только по каналу 1
	radio_writereg(EN_RXADDR, (1 << ERX_P0) | (1 << ERX_P1)); // включение каналов 0 и 1
	radio_writereg(SETUP_AW, SETUP_AW_5BYTES_ADDRESS); // выбор длины адреса 5 байт
	radio_writereg(SETUP_RETR, SETUP_RETR_DELAY_250MKS | SETUP_RETR_UP_TO_2_RETRANSMIT);
	radio_writereg(RF_CH, chan); // Выбор частотного канала
	radio_writereg(RF_SETUP, 0x26); // выбор скорости 1 Мбит/с и мощности 0dBm
	
	radio_writereg_buf(RX_ADDR_P0, &remote_addr[0], 5); // Подтверждения приходят на канал 0
	radio_writereg_buf(TX_ADDR, &remote_addr[0], 5);

	radio_writereg_buf(RX_ADDR_P1, &self_addr[0], 5);
	
	radio_writereg(RX_PW_P0, 32);
	radio_writereg(RX_PW_P1, 32);
	radio_writereg(DYNPD, (0 << DPL_P0) | (0 << DPL_P1)); // включение произвольной длины для каналов 0 и 1
	radio_writereg(FEATURE, (1<<EN_DYN_ACK)); // разрешение произвольной длины пакета данных

	radio_writereg(CONFIG, (1 << EN_CRC) |(1<<MASK_MAX_RT) | (1 << CRCO) | (1 << PWR_UP) | (1 << PRIM_RX)); // Включение питания
	return (radio_readreg(CONFIG) == ((1 << EN_CRC)|(1<<MASK_MAX_RT) | (1 << CRCO) | (1 << PWR_UP) | (1 << PRIM_RX))) ? 1 : 0;
}




void on_send_error() {
	// TODO здесь можно описать обработчик неудачной отправки
}

// Вызывается при получении нового пакета по каналу 1 от удалённой стороны.
// buf - буфер с данными, size - длина данных (от 1 до 32)
void on_packet(uint8_t * buf, uint8_t size) {
	// TODO здесь нужно написать обработчик принятого пакета

	// Если предполагается немедленная отправка ответа, то необходимо обеспечить задержку ,
	// во время которой чип отправит подтверждение о приёме
	// чтобы с момента приёма пакета до перевода в режим PTX прошло:
	// 130мкс + ((длина_адреса + длина_CRC + длина_данных_подтверждения) * 8 + 17) / скорость_обмена
	// При типичных условиях и частоте МК 8 мГц достаточно дополнительной задержки 100мкс
}



// Помещает пакет в очередь отправки.
// buf - буфер с данными, size - длина данных (от 1 до 32)

uint8_t send_data(uint8_t *buf, uint8_t size) {
	radio_deassert_ce(); // Если в режиме приёма, то выключаем его
	uint8_t conf = radio_readreg(CONFIG);
	if (!(conf & (1 << PWR_UP))) // Если питание по какой-то причине отключено, возвращаемся с ошибкой
	return 0;
	uint8_t status = radio_writereg(CONFIG, conf & ~(1 << PRIM_RX)); // Сбрасываем бит PRIM_RX
	if (status & (1 << TX_FULL_STATUS))  // Если очередь передатчика заполнена, возвращаемся с ошибкой
	return 0;
	radio_write_buf(W_TX_PAYLOAD_NOACK, buf, size); // Запись данных на отправку
	radio_assert_ce(); // Импульс на линии CE приведёт к началу передачи
	_delay_us(15); // Нужно минимум 10мкс, возьмём с запасом
	radio_deassert_ce();
	return 47;
}



void check_radio() {
	if (!radio_is_interrupt()) // Если прерывания нет, то не задерживаемся
	return;
	uint8_t status = radio_cmd(NOP);
	radio_writereg(STATUS, status); // Просто запишем регистр обратно, тем самым сбросив биты прерываний
	
	if (status & ((1 << TX_DS) | (1 << MAX_RT))) { // Завершена передача успехом, или нет,
		if (status & (1 << MAX_RT)) { // Если достигнуто максимальное число попыток
			radio_cmd(FLUSH_TX); // Удалим последний пакет из очереди
			on_send_error(); // Вызовем обработчик
		}
		if (!(radio_readreg(FIFO_STATUS) & (1 << TX_EMPTY))) { // Если в очереди передатчика есть что передавать
			radio_assert_ce(); // Импульс на линии CE приведёт к началу передачи
			_delay_us(15); // Нужно минимум 10мкс, возьмём с запасом
			radio_deassert_ce();
			} else {
			uint8_t conf = radio_readreg(CONFIG);
			radio_writereg(CONFIG, conf | (1 << PRIM_RX)); // Устанавливаем бит PRIM_RX: приём
			radio_assert_ce(); // Высокий уровень на линии CE переводит радио-чип в режим приёма
		}
	}
	uint8_t protect = 4; // В очереди FIFO не должно быть более 3 пакетов. Если больше, значит что-то не так
	while (((status & (7 << RX_P_NO)) != (7 << RX_P_NO)) && protect--) 
	{ // Пока в очереди есть принятый пакет
		uint8_t l = radio_read_rx_payload_width(); // Узнаём длину пакета
		if (l > 32) { // Ошибка. Такой пакет нужно сбросить
			radio_cmd(FLUSH_RX);
			} else {
			uint8_t buf[32]; // буфер для принятого пакета
			radio_read_buf(R_RX_PAYLOAD, &buf[0], l); // начитывается пакет
			if ((status & (7 << RX_P_NO)) == (1 << RX_P_NO)) 
			{ // если datapipe 1
				on_packet(&buf[0], l); // вызываем обработчик полученного пакета
			}
		}
		status = radio_cmd(NOP);
	}
}

// Основной цикл
int core(void) {
	radio_init();
	while (!radio_start()) {
		_delay_ms(1000);
	}
	// Перед включением питания чипа и сигналом CE должно пройти время достаточное для начала работы осциллятора
	// Для типичных резонаторов с эквивалентной индуктивностью не более 30мГн достаточно 1.5 мс
	_delay_ms(2);
	
	radio_assert_ce();
	
	for(;;) {
		check_radio();
		
		// TODO здесь основной код программы
	}
}