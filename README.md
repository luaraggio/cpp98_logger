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

- Esses design patterns utilizados foram implementados a partir de interfaces como recurso construtivo.
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

### Extensibilidade
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

In short, robust systems depend on visibility. A well-designed logger isn’t just a debugging tool, 'cause it’s an observability layer that tracks an application’s lifecycle without coupling logging logic to business logic. This logger was built around three core software design principles:

- Interface (abstraction via pure virtual class) — defines the contract for log event handling.
- Singleton Pattern — ensures a single global access point to the logger.
- Strategy Pattern — allows flexible output strategies (e.g., console, file, syslog).

---

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

