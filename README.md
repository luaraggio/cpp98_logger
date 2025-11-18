# Logger C++98

**Read this in other languages:**
🌐 [English](#english) | 🇧🇷 [Português](#português)

## português

# Logger C++98 — Interface, Singleton e Strategy Pattern

Neste projeto, implementei um **sistema de logging genérico** em **C++98**, projetado com princípios sólidos de **Programação Orientada a Objetos** e padrões de projeto (**Design Patterns**). O objetivo é oferecer uma base extensível, modular e segura para emissão de logs em aplicações single-threaded.

---

## Motivação

Resumidamente, sistemas robustos dependem de visibilidade. Um **logger bem projetado** não é apenas uma ferramenta de debug, porque também é uma **camada de observabilidade** que acompanha o ciclo de vida da aplicação, sem acoplar a lógica de logging à lógica de negócio.

Para isso, o logger que fiz aplica três pilares conceituais dentro de de software:

- **Interface (abstração via método virtual puro)** — define o contrato para tratamento de eventos de log.  
- **Design Patttern Singleton** — garante um ponto único de acesso ao logger.  
- **Design Pattern Strategy** — permite definir diferentes estratégias de saída (ex: console, arquivo, syslog).

Esses design patterns utilizados foram implementados a partir de interfaces como recurso construtivo.

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

## ⚙️ Conceitos-chave e como foram utilizados

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

### 2. Singleton Design Pattern
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

### 3. Strategy Design Pattern
Ao receber um evento, o Logger delega o processamento para a estratégia configurada:
```cpp
t_event event = { DEBUG, "Initialization complete" };
_instance->_handler->handleDebug(event);
```

- Isso permite que o comportamento do logger mude em tempo de execução, sem alterar seu código principal.

### Exemplo de uso que está na própria main.cpp
```cpp
class ConsoleHandler : public LogHandler {
public:
	void handleDebug(t_event e) { std::cout << "[DEBUG] " << e.message << std::endl; }
	void handleInfo(t_event e) { std::cout << "[INFO] " << e.message << std::endl; }
	void handleWarning(t_event e) { std::cout << "[WARNING] " << e.message << std::endl; }
	void handleError(t_event e) { std::cerr << "[ERROR] " << e.message << std::endl; }
};
```

```csharp
Saída:
[INFO] Application started.
[ERROR] Unexpected condition.
```

```cpp
int main() {
	ConsoleHandler console;
	Logger::initializeLogger(INFO, &console);

	Logger::info("Application started.");
	Logger::debug("This debug will not appear.");
	Logger::error("Unexpected condition.");
}
```

### Extensibilidade e Escalabilidade
Para criar uma nova estratégia de log, basta implementar a interface LogHandler:
```cpp
class FileHandler : public LogHandler {
	std::ofstream file;
public:
	FileHandler() : file("app.log", std::ios::app) {}
	void handleInfo(t_event e) { file << "[INFO] " << e.message << std::endl; }
	// ...
};
```
## Escrevendo o log diretamente para um arquivo
### FileLogHandler
O `FileLogHandler` grava eventos de log em um arquivo. Ele é usado para persistência, auditoria e armazenamento de logs fora do console.

- Principais características:
* Abre e gerencia um stream de saída para arquivo
* Escreve logs por nível de severidade
* Lida com falhas de I/O de arquivo de forma segura
* Funciona sozinho ou dentro de um `CompositeLogHandler`

- Quando usar:
* Quando os logs precisam persistir após a execução do programa
* Quando a depuração via arquivos é preferida
* Em ambientes de produção onde saída no console não é suficiente

## Para lidar com múltiplos handlers (para formas diferentes de outputs)
### CompositeLogHandler
O `CompositeLogHandler` envia eventos simultaneamente para múltiplos handlers.

- Principais características:
* Armazena uma coleção de handlers
* Encaminha cada evento para todos os handlers associados
* Permite pipelines de log com múltiplos destinos
* Implementa o padrão de projeto Composite

Ponto de observação importantíssimo: Nenhuma alteração é necessária na classe Logger, já que toda a sua construção é modular e se baseia em design patterns que delegam funções. Em outras palavras, partes do código chamam podem chamar o logger, mas o logger não precisa ser alterado. 

### Por que escolhi fazer em c++98? 
Porque além de ser a segunda linguagem que estou aprendendo na minha formação na 42Rio, depois de C, achei que seria um bom desafio desenvolver um logger sob as restrições do padrão C++98, com o propósito de aprofundar o entendimento sobre: 

- Implementação manual de Singletons (sem std::unique_ptr ou std::mutex)
- Uso de classes abstratas e virtual dispatch 
- Desacoplamento por interfaces puras
- Design Pattern Strategy aplicado de forma explícita

### 📚 Referências

- Design Patterns: Elements of Reusable Object-Oriented Software — Gamma et al. (GoF)
- Effective C++ — Scott Meyers 
- Documentação C++98 ISO/IEC 14882:1998(E)
- The Linux Programming Interface

> Esse logger foi projetado e implementado sob autoria de **Luara Raggio**
> como parte de um estudo aprofundado sobre design patterns e arquitetura de software em C++98
> O objetivo é demonstrar como princípios clássicos como *abstração*, *baixo acoplamento* e *responsabilidade única* se traduzem em implementações reais e escaláveis.

## english

In this project, I implemented a generic logging system in C++98, designed with strong Object-Oriented Programming principles and classic Design Patterns.
The goal is to provide an extensible, modular, and safe foundation for log handling in single-threaded applications.

---

## Motivation 

In short, robust systems depend on visibility. A well-designed logger isn’t just a debugging tool, 'cause it’s an observability layer that tracks an application’s lifecycle without coupling logging logic to business logic. To achieve this, the logger I built applies three conceptual pillars within software development:

- Interface (abstraction via pure virtual methods) — defines the contract for handling log events.
- Singleton Design Pattern — ensures a single point of access to the logger.
- Strategy Design Pattern — allows defining different output strategies (e.g., console, file, syslog).

These two design patterns were implemented using interfaces as the main structural resource.

## Architecture

### Conceptual Diagram

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

1. **Logger** is the global entry point. It filters messages based on `LogLevel` and delegates processing to a `LogHandler`. 
2. **LogHandler** is an abstract interface (a class with pure virtual methods) that defines how log events should be handled.
3. Concrete classes implement `LogHandler` to define different output strategies. For example:
   - `ConsoleHandler` → writes to `std::cout`
   - `FileHandler` → writes logs to a file
  
## ⚙️ **Key Concepts Used**

### 1. Interface (Abstraction)
The `LogHandler` class defines the contract for log consumption:
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

- This separates “what to do” from “how to do it,” allowing the logger to remain fully decoupled from the output mechanism.

### 2. Singleton Design Pattern
The Logger is accessible throughout the entire application, but only a single instance can exist:
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

- This ensures a global access point and consistency across modules.

### 3. Strategy Design Pattern
When an event is received, the Logger delegates the processing to the configured strategy:
```cpp
t_event event = { DEBUG, "Initialization complete" };
_instance->_handler->handleDebug(event);
```

- This allows the logger’s behavior to change at runtime without modifying its core code.

### Example in main.cpp
```cpp
class ConsoleHandler : public LogHandler {
public:
	void handleDebug(t_event e) { std::cout << "[DEBUG] " << e.message << std::endl; }
	void handleInfo(t_event e) { std::cout << "[INFO] " << e.message << std::endl; }
	void handleWarning(t_event e) { std::cout << "[WARNING] " << e.message << std::endl; }
	void handleError(t_event e) { std::cerr << "[ERROR] " << e.message << std::endl; }
};
```

```csharp
Saída:
[INFO] Application started.
[ERROR] Unexpected condition.
```

```cpp
int main() {
	ConsoleHandler console;
	Logger::initializeLogger(INFO, &console);

	Logger::info("Application started.");
	Logger::debug("This debug will not appear.");
	Logger::error("Unexpected condition.");
}
```

### Extensibility and Scalability
To create a new logging strategy, simply implement the `LogHandler` interface:
```cpp
class FileHandler : public LogHandler {
	std::ofstream file;
public:
	FileHandler() : file("app.log", std::ios::app) {}
	void handleInfo(t_event e) { file << "[INFO] " << e.message << std::endl; }
	// ...
};
```

## Writing log directly to a file
### FileLogHandler
The `FileLogHandler` writes log events to a file. It is used for persistence, auditing, and storing logs outside the console

- Key Features:
* Opens and manages an output file stream.
* Writes logs by severity level.
* Handles file I/O failures gracefully.
* Works standalone or inside a CompositeLogHandler.

- When to Use:
* When logs must persist beyond program execution.
* When debugging via files is preferred.
* When operating in production environments where console output is not sufficient.

## Dealing with multiple handlers and output forms
### CompositeLogHandler
The `CompositeLogHandler` broadcasts events to multiple handlers simultaneously

- Key Features
* Stores a collection of handlers.
* Forwards every event to all attached handlers.
* Enables multi-target logging pipelines.
* Implements the Composite design pattern.

Important Observation: No changes are required in the Logger class, since its entire construction is modular and based on design patterns that delegate responsibilities. In other words, parts of the code may call the logger, but the logger itself never needs to be modified.

### Why did I choose to build this in C++98?
Because aside from being the second language I’m learning at 42Rio — after C — I thought it would be a great challenge to implement a logger under the constraints of the C++98 standard, with the purpose of deepening my understanding of:

- Manual Singleton implementation (without std::unique_ptr or std::mutex)
- Use of abstract classes and virtual dispatch
- Decoupling through pure interfaces
- Explicit application of the Strategy design pattern using interfaces

### 📚 References

- Design Patterns: Elements of Reusable Object-Oriented Software — Gamma et al. (GoF)
- Effective C++ — Scott Meyers 
- Documentação C++98 ISO/IEC 14882:1998(E)
- The Linux Programming Interface

> This logger was designed and implemented by Luara Raggio
> as part of an in-depth study on design patterns and software architecture in C++98
> The goal is to demonstrate how classical principles such as abstraction, low coupling, and single responsibility translate into real, scalable implementations.
