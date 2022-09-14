# clean-it

This project is provided as a demo that accompanies the talk: "Your Compiler Understands It, But Does Anyone Else (CppCon2022)"  

# Build

Install the following third party libraries as sibling directories of this repo.
1. boost_1_80_0
2. cppcoro (https://github.com/andreasbuhr/cppcoro)
3. Hypodermic (https://github.com/ybainier/Hypodermic)
4. Open clean-it.sln with Visual Studio and build (only the debug configuration is ready).

# Tags

 * v1-MovieReader   
 This is the initial implementation of the MovieReader.  
 
 * v2-header-ordering   
 Reordering headers according to the recommendations in the presentation.  
 
 * v3-with-tl-expected   
 Integrated tl/expected to avoid throwing.  
 
 * v4-using-generator  
 Using cppcoro::generator for lazy loading of the movies.  
 
 * v5-VODServer-VODClient  
 First implementation of the VODServer and the VODClient.  
 
 * v5-avoid-primitive-obsession  
 Redesign of the Movie class to ensure that invalid objects cannot be created.  
 
 * v6-use-dependency-injection  
 Implemented interfaces and injection of dependencies as interfaces into ctor.  
 
 * v7-use-ioc-container  
 Integrated "hypodermic" as IOC container.  
 
 * v8-prefer-composition-over-inheritance  
 Implement logging as injected interface rather than implementation inheritance.  
 
 * v9-use-header-unit-for-std    
 Created static libraries that contain header units for standard and thirdparty headers.
 
 * v10-VOD-as-a-module  
 Made VOD itself a module.  
 
 
 
