# Logger em C++98 — Interface, Singleton e Strategy Pattern

Neste projeto, implementei um **sistema de logging genérico** em **C++98**, projetado com princípios sólidos de **Programação Orientada a Objetos** e padrões de projeto (**Design Patterns**). O objetivo é oferecer uma base extensível, modular e segura para emissão de logs em aplicações single-threaded.

---

## Motivação

Resumidamente, sistemas robustos dependem de visibilidade. Um **logger bem projetado** não é apenas uma ferramenta de debug, porque também é uma **camada de observabilidade** que acompanha o ciclo de vida da aplicação, sem acoplar a lógica de logging à lógica de negócio.

Para isso, o logger que fiz aplica três pilares do design de software:

- **Interface (abstração via classe pura)** — define o contrato para tratamento de eventos de log.  
- **Singleton Pattern** — garante um ponto único de acesso ao logger.  
- **Strategy Pattern** — permite definir diferentes estratégias de saída (ex: console, arquivo, syslog).

---

## Arquitetura

### Diagrama Conceitual

```
Application
      │
      ▼
Logger (Singleton)
      │
      ▼
LogHandler (Interface)
      │
┌─────┴───────────┐
▼                 ▼
ConsoleHandler  FileHandler
```

1. **Logger** é o ponto de entrada global. Ele filtra mensagens com base no `LogLevel` e delega o processamento para um `LogHandler`.  
2. **LogHandler** é uma **interface abstrata** (classe com métodos virtuais puros) que define *como* eventos de log devem ser tratados.  
3. Classes concretas implementam `LogHandler` para definir diferentes estratégias de output — por exemplo:
   - `ConsoleHandler` → escreve no `std::cout`
   - `FileHandler` → grava logs em um arquivo

## ⚙️ Design Patterns Utilizados

### 1. Interface (Abstração)
A classe `LogHandler` define o *contrato* de consumo de logs:
```cpp
class LogHandler {
public:
	virtual ~LogHandler() {}
	virtual void handleDebug(t_event event) = 0;
	virtual void handleInfo(t_event event) = 0;
	virtual void handleWarning(t_event event) = 0;
	virtual void handleError(t_event event) = 0;
};
```

- Isso separa o “o que fazer” do “como fazer”, permitindo que o logger seja totalmente desacoplado da forma de saída.

### 2. Singleton Pattern
O Logger é acessível por toda a aplicação, mas só pode haver uma instância:
```cpp
class Logger {
private:
	static Logger* _instance;
	Logger(LogLevel level, LogHandler* handler);
public:
	static int initializeLogger(LogLevel level, LogHandler* handler);
	static void debug(std::string message);
	// ...
};
```

- Isso garante um ponto global de acesso e consistência entre módulos.

### 3. Strategy Pattern
Ao receber um evento, o Logger delega o processamento para a estratégia configurada:
```cpp
t_event event = { DEBUG, "Initialization complete" };
_instance->_handler->handleDebug(event);
```

- Isso permite que o comportamento do logger mude em tempo de execução, sem alterar seu código principal.

### 📚 Referências

- Design Patterns: Elements of Reusable Object-Oriented Software — Gamma et al. (GoF)
- Effective C++ — Scott Meyers 
- Documentação C++98 ISO/IEC 14882:1998(E)
- The Linux Programming Interface


