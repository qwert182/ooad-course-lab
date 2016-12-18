#pragma once

#include "IResource.h"

class ProjectsResource : public IResource {
	ProjectsResource(const ProjectsResource &);
public:
	ProjectsResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~ProjectsResource() {}
};

