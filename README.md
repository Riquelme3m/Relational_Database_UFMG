# Project Title: Relational Database Concepts

## Introduction
This repository illustrates the full lifecycle of a database design project, grounded in the relational model as initially proposed by Edgar F. Codd. It includes the conceptual design of the miniworld, Entity-Relationship modeling, conversion to Codd's relational schema,creation of a table to represent the metadata and the physical implementation in SQL.

## Database Design Phases

### Phase 1: Conceptual Design (Miniworld)
The first phase involves understanding the requirements from the client and creating the miniworld. The miniworld is a term used to describe the real-world environment that the database is intended to simulate. Here, requirements gathering occurs to identify all entities, their relationships, and the key constraints without considering database technology.

#### Entity-Relationship Model
- **Purpose**: To visually represent entities, their attributes, and relationships in an abstract way.
- **Tools Used**: Draw.io.
- **Outcome**: An ER diagram that provides a high-level, technology-agnostic overview of data organization.

### Phase 2: Logical Design
This phase translates the ER model from the conceptual design into a logical data model that adheres to specific database management system rules. This involves defining tables, keys, and constraints based on Codd’s relational model.Additionally , the metadata for the physical implementation is also created to facilitate the implementation.

#### Data Relational Model Proposed by Codd
- **Principles**: Focus on tables (relations), rows (tuples), and columns (attributes).
- **Normalization**: Apply normalization rules to reduce redundancy and dependencies.
- **Outcome**: A set of normalized tables, each with defined primary keys and established relationships.

### Phase 3: Physical Implementation
The final phase involves translating the logical model into a physical model that performs efficiently on a specific database management system.

- **SQL Implementation**: Scripts are written to create tables, constraints, indexes, and relationships.
- **Performance Optimization**: Includes indexing strategies and optimizations specific to the chosen DBMS.
- **Testing and Validation**: Ensuring the database meets all functional and non-functional requirements.

## Technologies Used
- C++ (Connector C++ to connect to the database)
- SQL (MySQL)
- Diagramming Tools (Draw.io)
- Git for version control

